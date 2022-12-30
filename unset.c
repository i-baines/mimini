/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:32 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:33 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_make_unset(char *src, t_mini *mini, int line)
{
	char **new_env;
	int	i;

	i = 0;
	mini->env_len = 0;
	while (mini->env[mini->env_len])
		mini->env_len ++;
	new_env = (char **)malloc(sizeof(char *) * (mini->env_len));

	while (mini->env[i + 1])
	{
		if (i < line)
			new_env[i] = ft_strdup(mini->env[i]);
		else
			new_env[i] = ft_strdup(mini->env[i + 1]);
		i++;
	}
	new_env[i] = NULL;
	ft_free_malloc2(mini->env);
	mini->env = new_env;
}

void	ft_unset(char **src, t_mini *mini)
{
	int		i;

	i = 0;
	if (ft_matrix_len(src) != 1)
	{
		while (mini->env[i])
		{
			if (ft_strncmp(src[1], mini->env[i], ft_check_var2(src[1])) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(src[1])))
			{
				ft_make_unset(src[1], mini, i);
				ft_exit(0);
				return ;
			}
			i++;
		}
	}
	ft_exit(0);
}