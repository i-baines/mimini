/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_com2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:08 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:09 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}


void	ft_putstr2(char *str, char **path)
{
	ft_putstr("Minishell: command not found: ");
	ft_putstr(str);
	ft_putstr("\n");
	ft_free_malloc2(path);
	ft_exit(127);
	exit(127);
}

int	ft_get_command(char **argcc, char **env)
{
	int		x;
	int		i;
	int		y;
	char	*ptr;
	char	**path;

	i = 0;
	path = ft_getpath(env);
	if (!path)
		printf("Minishell: %s command not found\n", argcc[0]);
	while (path && path[i])
	{
		ptr = ft_strjoin(path[i], argcc[0]);
		x = access(ptr, X_OK);
		y = access(argcc[0], X_OK);
		if (x == 0 || y == 0)
		{
			printf("aaaaaaa=%s\n", argcc[0]);
			ft_free_malloc2(path);
			path = NULL;
			if (y == 0)
				execve(argcc[0], &argcc[0], env);
			execve(ptr, &argcc[0], env);
		}
		else
		{
			if (i == (ft_get_size(path) - 1))
				ft_putstr2(argcc[0], path);
		}
		free(ptr);
		i++;
	}
	if (path)
		ft_free_malloc2(path);
	if (!path) // igual hay que liberar el path
		exit (-1);
	path = NULL;
	return (0);
}