/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:55:54 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 12:55:55 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_swap(char *str, t_mini *mini)
{		
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (mini->env[i] && i < mini->env_len - 1)
	{
		if (ft_strncmp("PWD", mini->env[i], ft_check_var2("PWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("PWD")))
		{	
			ptr = mini->env[i];//ahora antiguo
			mini->env[i] = ft_strjoin("PWD=", str); // juntar  
		}
		if (ft_strncmp("OLDPWD", mini->env[i], ft_check_var2("OLDPWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("OLDPWD")))
		{	
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD", ptr + 3);
			free(ptr);
		}
		i++;
	}
	free(str);
	return(0);
}

int	ft_swap_pwd(char *str, t_mini *mini)
{
	int		i;
	char	*ptr;

	i = 0;
	while (mini->env[i] && i < mini->env_len - 1)
	{
		if (ft_strncmp("PWD", mini->env[i], ft_check_var2("PWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("PWD")))
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("PWD", str + 6);
		}
		i++;
	}
	return(0);
}

int	ft_cd_find(char *str, t_mini *mini)
{		
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (mini->env[i] && i < mini->env_len - 1)
	{
		if (ft_strncmp(str, mini->env[i], ft_check_var2(str)) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(str)))
		{
			//printf("i = %d\n");
			return (i);
		}
		i++;
	}
	return(0);
}

int		ft_cd(char **str, t_mini *mini)
{
	int	dim;

	dim = 0;
	while (str[dim])
		dim++;
	if (dim != 1)
	{
		printf("A\n");
		if (chdir(str[1]) == -1 && str[1][0] != '-')
		{
			printf("cd: no such file or directory: %s\n", str[1]);
			return (0);
		}
		if (dim >= 2 && str[1][0] == '-' && chdir(mini->env[ft_cd_find("OLDPWD", mini)] + 7) == -1)
		{
			printf("cd: no such file or directory: %s\n", mini->env[ft_cd_find("OLDPWD", mini)] + 7);
			return (0);
		}
	}
	else if (chdir(ft_gethome(mini)) == -1 && ft_gethome(mini) != NULL)
	{
		printf("cd: no such file or directory: %s\n", ft_gethome(mini));
		return (0);
	}
	else if (chdir(ft_gethome(mini)) == -1 && ft_gethome(mini) == NULL)
	{
		printf("MINISHELL: cd: HOME not set\n");
		return (0);
	}
	ft_cd_swap(ft_pwd(), mini);
	return (1);
}