/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:24 by ibaines           #+#    #+#             */
/*   Updated: 2023/01/02 12:22:27 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_one_com(char **cmd, t_mini *mini)
{
	/*int	first_pipe;

	first_pipe = 0;
	if (ft_matrix_len(cmd) == 1)
	{
		printf("dim = %d\n", ft_matrix_len(cmd));
		first_pipe = dup(0);
		dup2 (first_pipe, STDIN_FILENO);
	}*/
		ft_get_command(cmd, mini->env);
	//	close (first_pipe);
}

int	my_exit(char **src, t_mini *mini)
{
	int i;
	int	j;

	i = 0;
	j = 1;
	if (ft_matrix_len(src) <= 2)
	{
		while (src[j][i])
		{
			if (!ft_isdigit(src[j][i]) && src[j][i] != ' ')
			{
				printf("exit\nMinishell: exit: %s: numeric argument required\n", src[j]);
				g_error = 255;
				exit(0);
			}
			i++;
		}
		i = 0;
		//j++;
		printf("num = %s\n",src[j]);
		//printf("num = %d\n",ft_atoi(src[j]));
		g_error = ft_atoi(src[j]);
		exit(0);
	}
	printf("exit\nMinishell: exit: too many arguments\n");
	g_error = 1;
}

int checker(char **paths, char **src, t_mini *mini)
{
	int pid;
	char **command;

	if (ft_strlen(src[0]) == 4 && !ft_strncmp(src[0], "exit", 4))
		my_exit(src, mini);
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
	printf("******\n");
	ft_one_com(src, mini);
	return (0);
}

int	ft_checkcom(char **src)
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