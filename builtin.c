/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:29 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:30 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printpwd(void)
{
	char	tmp[PATH_MAX];

	if (getcwd(tmp, sizeof(tmp)) == 0)
	{
		printf("Error getcwd\n");
		return ;
	}
	printf("%s\n", tmp);
}

char	*ft_pwd(void)
{
	char	tmp[PATH_MAX];
	char	*dir;

	if (getcwd(tmp, sizeof(tmp)) == 0)
	{
		printf("Error getcwd\n");
		return (NULL);
	}
	//printf("%s\n", tmp);
	dir = ft_strdup(tmp);
	return (dir);
}

int	ft_echo(char **src, t_mini *mini)
{
	int dim;
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	dim = 0;
	while (src[dim])
		dim++;
	if (dim >= 2)
	{
		while (ft_strlen(src[i]) == 2 && !ft_strncmp(src[i], "-n", 2))
		{
			flag = 1;
			i++;
		}
		if (flag == 1)
		{
			while (src[i])
			{
				printf("%s", src[i]);	
				i++;
			}
		}
		else
		{
			while (src[i])
			{
				if (src[i + 1])
					printf("%s ", src[i]);	
				else
					printf("%s", src[i]);	
				i++;
			}
			printf("\n");
		}
	}
}

void	ft_env(t_mini *mini)
{
	int i;

	i = 0;
	while(mini->env[i])
	{		
		if (ft_strchr(mini->env[i], '='))
			printf("%s\n", mini->env[i]);
		i++;
	}
}