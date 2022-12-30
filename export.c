/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:40 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:41 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export2(t_mini *mini, int i)
{
	int j;

	write(1, "\"", 1);
	j = ft_strlen_export(mini->env[i]) + 1;
	while (j <= ft_strlen(mini->env[i] + ft_strlen_export(mini->env[i])))
	{
		write(1, &mini->env[i][j], 1);
		j++;
	}
	write(1, "\"", 1);
}

void	ft_print_export(t_mini *mini)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (mini->env[i])
	{
		write(1, "declare -x ", 11);
		while (j <= ft_strlen_export(mini->env[i]))
		{
			write(1, &mini->env[i][j], 1);
			j++;
		}
		if (ft_strchr(mini->env[i], '='))
			ft_print_export2(mini, i);
		j = 0;
		write(1, "\n", 1);
		i++;
	}
}

int	ft_strlen_export(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return(i);
}

void	ft_make_export(char *src, t_mini *mini)
{
	int		i;
	char	**new_env;

	i = 0;
	while (mini->env[i])
		i++;
	i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (mini->env[i])
	{
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(src);
	i++;
	new_env[i] = NULL;
	ft_free_malloc2(mini->env);
	mini->env = new_env;
}

int	ft_valid_export(char *src)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (src[i] && src[i] != '=')
	{
		if (!ft_isalnum(src[i]))
		{
			printf("Minishell: export: %s: not a valid identifier\n", src);
			return(0);
		}
		i++;
	}
	return(1);
}

void	ft_export(char **src, t_mini *mini) // copiar env y añadir el export
{
	int i;

	i = 1;
	if (ft_matrix_len(src) == 1)
		ft_print_export(mini);
	while (src[i])
	{
		if (ft_valid_export(src[i]))
		{
			if (!ft_check_var(src[i], mini))
			{
				ft_make_export(src[i], mini);
				ft_exit(0);
			}
			ft_exit(0);
		}
		i++;
	}
}