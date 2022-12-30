/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:24 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:25 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_one_com(char **cmd, t_mini *mini)
{
	int	first_pipe;

	first_pipe = 0;
	if (ft_matrix_len(cmd) == 1)
	{
	printf("dim = %d\n", ft_matrix_len(cmd));
		first_pipe = dup(0);
		dup2 (first_pipe, STDIN_FILENO);
		//close (first_pipe);

	}
		//checker_inpipe(mini->env, cmd, mini);
		//ft_get_command(cmd, mini->env);
		//ft_free_malloc2(cmd);
		ft_get_command(cmd, mini->env);
		close (first_pipe);
}

int checker(char **paths, char **src, t_mini *mini)
{
	int pid;
	char **command;
	//if (paths)
	//	ft_free_malloc2(paths);
	if (ft_strlen(src[0]) == 4 && !ft_strncmp(src[0], "exit", 4))
		exit (-1);
	else if (ft_strlen(src[0]) == 3 && !ft_strncmp(src[0], "env", 3))
	{	
		ft_env(mini);
		return(0);
	}
	else if (ft_strlen(src[0]) == 4 && !ft_strncmp(src[0], "echo", 4))
	{	
		ft_echo(src, mini);
		return(0);
	}
	else if (ft_strlen(src[0]) == 6 && !ft_strncmp(src[0], "export", 6))
	{	
		ft_export(src, mini);
		return(0);
	}
	else if (ft_strlen(src[0]) == 5 && !ft_strncmp(src[0], "unset", 5))
	{	
		ft_unset(src, mini);
		return(0);
	}
	else if (ft_strlen(src[0]) == 2 && !ft_strncmp(src[0], "cd", 2))
	{	
		ft_cd(src, mini);
		return(0);
	}
	else if (ft_strlen(src[0]) == 3 && !ft_strncmp(src[0], "pwd", 3))
	{	
		ft_printpwd();
		return(0);
	}
	ft_one_com(src, mini);
	return (0);
}

int	ft_checkcom(char **src) // comprobar comandos cd, unset, export, exit
{
	int	i;

	i = 0;
	while (src[0][i])
		i++;
	if (ft_strlen("cd") == i && !ft_strncmp(src[0], "cd", 2))
		return (1);
	if (ft_strlen("unset") == i && !ft_strncmp(src[0], "unset", 5))
		return (1);
	if (ft_strlen("export") == i && !ft_strncmp(src[0], "export", 6))
		return (1);
	if (ft_strlen("exit") == i && !ft_strncmp(src[0], "exit", 4))
		return (1);
	else
		return (0);
}