/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:56:05 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:56:06 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_malloc2(char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		free(src[i]);
		i++;
	}
	free(src);
	return(1);
}

char **ft_malloc(char **src, t_mini *mini)
{
	char	**save;
	int		i;
	int		n;

	i = 0;
	while (src[i])
	{
		i++;
	}
	n = i;
	save = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (i < n)
	{
		save[i] = ft_strdup(src[i]);
		i++;
	}
	save[i] = NULL;
	i--;
	mini->env_len = i;
	return(save);
}

void	ft_freeall(t_mini *mini)
{
	printf("a\n");
	ft_free_malloc2(mini->env);
	exit(1);
}