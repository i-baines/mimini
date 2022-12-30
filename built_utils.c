/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:21 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:22 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getpath(char **env)
{
	int		i;
	char	*ptr;
	char	**path;
	int		find;

	find = 0;
	i = 0;
	while (env[i])
	{
		ptr = strstr(env[i], "PATH=");
		if (ptr)
		{
			find = 1;
			break ;
		}
		i++;
	}
	if (find)
		path = ft_splitraro(ptr + 5, ':');
	else
		path = NULL;
	return (path);
}

int	ft_check_var2(char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	return(i);
}

int	ft_check_var(char *src, t_mini *mini)
{		
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(src, mini->env[i], ft_check_var2(src)) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(src)))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(src);
			return(1);
		}
		i++;
	}
	return(0);
}

///
char	*ft_gethome(t_mini *mini)
{
	int		i;
	char	*ptr;

	i = 0;
	while (mini->env[i] && i < mini->env_len - 1)
	{
		if (ft_strncmp("HOME", mini->env[i], ft_check_var2("HOME")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("HOME")))
			return(mini->env[i] + 5);
		i++;
	}
	return(NULL);
}