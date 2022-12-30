/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:56:16 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:56:17 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int checker_inpipe(char **paths, char **src, t_mini *mini)//cambiar exit por return para liberar
{	
	if (ft_strlen(src[0]) == 4 && !ft_strncmp(src[0], "exit", 4))
		exit (-1);
	else if (ft_strlen(src[0]) == 3 && !ft_strncmp(src[0], "env", 3))
	{	
		ft_env(mini);
		ft_free_malloc2(src);
		src = NULL;
		exit(-1);
	}
	else if (ft_strlen(src[0]) == 4 && !ft_strncmp(src[0], "echo", 4))
	{	
		ft_echo(src, mini);
		ft_free_malloc2(src);
		src = NULL;
		exit(-1);
	}
	else if (ft_strlen(src[0]) == 6 && !ft_strncmp(src[0], "export", 6))
	{	
		ft_export(src, mini);
		ft_free_malloc2(src);
		src = NULL;
		exit(-1);
	}
	else if (ft_strlen(src[0]) == 5 && !ft_strncmp(src[0], "unset", 5))
	{	
		ft_unset(src[1], mini);
		ft_free_malloc2(src);
		src = NULL;
		exit(-1);
	}
	else if (ft_strlen(src[0]) == 2 && !ft_strncmp(src[0], "cd", 2))
	{	
		ft_cd(src, mini);
		exit(-1);
	}
	else if (ft_strlen(src[0]) == 3 && !ft_strncmp(src[0], "pwd", 3))
	{	
		ft_printpwd();
		ft_free_malloc2(src);
		src = NULL;
		exit(-1);
	}
	ft_get_command(src, mini->env);
	return (0);
}

int	ft_lastpipe(char **cmd, int *first_pipe, t_mini *mini)
{
	int	cpid;

	cpid = fork ();
	if (cpid == 0)
	{
		dup2 (*first_pipe, STDIN_FILENO);
		close (*first_pipe);
		checker_inpipe(mini->env, cmd, mini);
		//ft_get_command(cmd, mini->env);
		//ft_free_malloc2(cmd);
	}
	else
	{
		close (*first_pipe);
		waitpid(cpid, NULL, 0);
	}
}

int	ft_firstpipes(char **cmd, int *first_pipe, t_mini *mini)
{
	int	pipefd[2];
	int	cpid;

	pipe (pipefd);
	cpid = fork ();
	if (cpid == 0)
	{
		close (pipefd[0]);
		dup2 (pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
		dup2 (*first_pipe, STDIN_FILENO);
		close (*first_pipe);
		checker_inpipe(mini->env, cmd, mini);
		//ft_get_command(cmd, mini->env);
		//ft_free_malloc2(cmd);
		//cmd = NULL;
	}
	else
	{
		close (pipefd[1]);
		close (*first_pipe);
		*first_pipe = pipefd[0];
	}
}

int	ft_pipes(t_mini *mini)
{
	int	first_pipe;
	int	i;
	int	dim;

	i = 0;
	dim = ft_matrix_len(mini->split_pipe);
	first_pipe = dup(0);
	while (mini->split_pipe[i])
	{
		if (i != 0)
		{
			mini->split_quote = ft_split_quotes(mini->split_pipe[i]);
			dequoter(mini->split_quote);
		}
		if ( i < dim - 1)
			ft_firstpipes(mini->split_quote, &first_pipe, mini);
		else if (i == dim -1)
			ft_lastpipe(mini->split_quote, &first_pipe, mini);
		i++;
		ft_free_malloc2(mini->split_quote);
	}
	ft_free_malloc2(mini->split_pipe);
	mini->split_pipe = NULL;
}