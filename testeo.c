/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:14:39 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/20 19:04:52 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include <string.h>
#define BOLD	"\001\033[1m\002"
#define CLOSE	"\001\033[0m\002"
#include <stdlib.h>
#include <signal.h>

int g_error;

void 	ft_print(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}	
}

void	ft_exit(int num)
{
	g_error = num;
}

void sighandler(int signum)
{
	char c;

	c = 127;
	//printf("%d\n", signum);
    if (signum == 2)
   {  
		//write(1, &c, 1);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
}
}

static int	ft_len_ptr(char *s, char c)
{
	int	i;
	int	len;
	int	ptr;

	len = 0;
	i = 0;
	ptr = 0;
	if (c == '\0' && s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			len++;
			i++;
		}
		if (len > 0)
		{
			ptr++;
			len = 0;
		}
	}
	return (ptr);
}

static int	ft_res_word(char *s, int len, int i, char **ptr)
{
	char	*wptr;

	len++;
	wptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!wptr)
		return (-1);
	wptr[len] = '\0';
	wptr[len - 1] = '/';
	len = len - 2;
	while (len >= 0)
	{
		wptr[len] = s[len + i];
		len--;
	}
	*ptr = wptr;
	return (0);
}

static int	ft_get_word(char *s, char c, char **ptr, int ptrlen)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	while (s[i] == c)
		i++;
	j = i;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	if (len > 0)
	{
		if (ft_res_word(s, len, j, ptr))
			return (-1);
	}
	if (ptrlen > 1)
		ft_get_word(s + i, c, &ptr[k + 1], ptrlen - 1);
	return (0);
}
static char	**ft_res_pointer(int ptr)
{
	char	**string;
	char	*ptrs;

	string = (char **)malloc((ptr + 1) * sizeof (ptrs));
	if (!string)
		return (NULL);
	return (string);
}

char	**ft_splitraro(char const *s, char c)
{
	int		ptr;
	char	**array;

	if (!s)
		return (NULL);
	ptr = ft_len_ptr((char *)s, c);
	array = ft_res_pointer(ptr);
	if (ptr > 0)
	{
		if (ft_get_word((char *)s, c, array, ptr))
			return (NULL);
	}
	array[ptr] = NULL;
	return (array);
}

void	ft_putstr(char *str)
{	
	while (*(str) != '\0')
	{	
		write(2, str, 1);
		str = str + 1;
	}
}


void	ft_putstr2(char *str)
{
	ft_putstr("zsh: command not found: ");
	ft_putstr(str);
	ft_putstr("\n");
	ft_exit(127);
	exit(127);
}

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

int	ft_get_command(char **argcc, char **env)
{
	int		x;
	int		i;
	char	*ptr;

	i = 0;
	while (env[i])
	{
		ptr = ft_strjoin(env[i], argcc[0]);
		x = access(ptr, X_OK);
		if (x == 0)
			execve(ptr, &argcc[0], env);
		else
		{
			if (i == (ft_get_size(env) - 1))
				ft_putstr2(argcc[0]);
		}
		free(ptr);
		i++;
	}
	return (0);
}

char **ft_first_check(char *src)
{
	char **ptr;

	ptr = ft_split(src, '|');
	if (!ptr)
		return(NULL);
	return(ptr);
}

void	ft_env(t_mini *mini)
{
	int i;

	i = 0;
	while(mini->env[i])
	{		
		printf("%s\n", mini->env[i]);
		i++;
	}
}


char	**ft_getpath(char **env)
{
	int		i;
	char	*ptr;
	char	**path;

	i = 0;
	while (env[i])
	{
		ptr = strstr(env[i], "PATH=");
		if (ptr)
			break ;
		i++;
	}
	path = ft_splitraro(ptr + 5, ':');
	return (path);
}

int	ft_strlen_export(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return(i);
}

int	ft_check_var2(char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	// printf("%c ", src[i]);
	// printf("%d\n", i);
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

void	ft_make_export(char *src, t_mini *mini)
{
	int		i;
	char	**new_env;

	i = 0;
	while (mini->env[i])
		i++;
	i++;
	//printf("mtrx len-> %d\n", i);
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (mini->env[i])
	{
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
		// printf("%d\n",i);
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

void	ft_unset(char *src, t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(src, mini->env[i], ft_check_var2(src)) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export(src)))
		{
			ft_make_unset(src, mini, i);
			ft_exit(0);
			return ;
		}
		i++;
	}
	ft_exit(0);
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

int	ft_cd_swap1(char *str, t_mini *mini)
{		
	int		i;
	int		j;
	char	*ptr;
	char	*tmp;

	i = 0;
	j = 0;
	while (mini->env[i] && i < mini->env_len - 1)
	{
		if (ft_strncmp("PWD", mini->env[i], ft_check_var2("PWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("PWD")))
			ptr = mini->env[i];//ahora antiguo
		if (ft_strncmp("OLDPWD", mini->env[i], ft_check_var2("OLDPWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("OLDPWD")))
		{	
			tmp = ft_strdup(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD", ptr + 3);
			ft_swap_pwd(tmp, mini);
			free(tmp);
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

int	ft_cd_swap2(char *str, t_mini *mini)
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
			while(mini->env[i][j])
				j++;
			j = j - 2;
			while(mini->env[i][j] != '/')
				j--;
			mini->env[i] = (char *)malloc(j + 1);
			ft_strncpy(mini->env[i], ptr, j);
			mini->env[i][j] = '\0';
		}
		if (ft_strncmp("OLDPWD", mini->env[i], ft_check_var2("OLDPWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("OLDPWD")))
		{	
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD", ptr + 3);
			free(ptr);
		}
		i++;
	}
	return(0);
}

int	ft_cd_swap3(char *str, t_mini *mini)
{		
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (mini->env[i] && i < mini->env_len - 1)
		if (ft_strncmp("PWD", mini->env[i], ft_check_var2("PWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("PWD")))
			ptr = mini->env[i];//ahora antiguo
		if (ft_strncmp("OLDPWD", mini->env[i], ft_check_var2("OLDPWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("OLDPWD")))
		{	
			free(mini->env[i]);
	{
			mini->env[i] = ft_strjoin("OLDPWD", ptr + 3);
			//free(ptr);
		}
		i++;
	}
	return(0);
}

int	ft_cd_swap4(t_mini *mini)
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
			mini->env[i] = ft_strjoin("PWD=", ft_gethome(mini));
		}
		if (ft_strncmp("OLDPWD", mini->env[i], ft_check_var2("OLDPWD")) == 0 && (ft_strlen_export(mini->env[i]) == ft_strlen_export("OLDPWD")))
		{	
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD", ptr + 3);
			free(ptr);
		}
		i++;
	}
	return(0);
}

int	ft_check_cd(char *str, t_mini *mini)
{
	if (ft_strlen(str - 3) == 2)
	{
		printf("MINISHELL: cd: HOME not set\n");
		if (ft_gethome(mini) == NULL)
		{
			return(0);
		}
		ft_cd_swap4(mini);
		return(0);
	}
	if (ft_strlen(str) == 1 && str[0] == '-')
	{
		ft_cd_swap1(str, mini);
		return(0);
	}
	if (ft_strlen(str) == 2 && !ft_strncmp("..", str, 2))

	{
		ft_cd_swap2(str, mini);
		return (-1);
	}
	if (ft_strlen(str) == 1 && str[0] == '.')
	{
		ft_cd_swap3(str, mini);
		return (0);
	}
	return (-1);
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
				printf("%s ", src[i]);	
				i++;
			}
			printf("\n");
		}
	}
}

int checker(char **paths, char **src, t_mini *mini)
{
	int pid;
	char **command;
	
	//command = ft_split(src, ' ');
	if (!ft_strncmp(src[0], "exit", 4))
		exit (-1);
	else if (!ft_strncmp(src[0], "env", 3))
	{	
		ft_env(mini);
		return(0);
	}
	else if (!ft_strncmp(src[0], "echo", 4))
	{	
		ft_echo(src, mini);
		return(0);
	}
	else if (!ft_strncmp(src[0], "export", 6))
	{	
		ft_export(src, mini);
		return(0);
	}
	else if (!ft_strncmp(src[0], "unset", 5))
	{	
		ft_unset(src[1], mini);
		return(0);
	}
	else if (!ft_strncmp(src[0], "cd", 2))
	{	
		//printf("S\n");
		ft_cd(src, mini);
		return(0);
	}
	else if (!ft_strncmp(src[0], "pwd", 3))
	{	
		ft_printpwd();
		return(0);
	}
	ft_get_command(src, paths);
	/*else if (ft_strlen(src) > 0)
	{
		pid = fork();
		if (pid == 0)
		else
		{
			waitpid(pid, NULL, 0);
		}
	}*/
	return (0);
}

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
	//printf("%s\n", src[i]);
	save = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (i < n)
	{
		//printf("%d\n", i);
		save[i] = ft_strdup(src[i]);
		i++;
	}
	save[i] = NULL;
	i--;
	mini->env_len = i;
	return(save);
}



//void 	ft_getquote(char **str){}

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

int	main(int argc, char **argv, char **env)
{
	//const char	*src;
	char		*ptr;
	char		**ptr2;
	char		**splited_argv;
	t_mini 		mini;
	int i;
	int	pid; ///

	mini.env = ft_malloc(env, &mini);
	i = 0;
 	g_error = 0;
	ft_print(mini.env);
   	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	signal(SIGABRT, sighandler);
	i = 0;
	ptr2 = ft_getpath(env);
	argv[1] = NULL;
	i = argc;
	i = 0;
	while (1) // separar comandos que hace el padre a los hijos
	{
		ptr = readline(BOLD "Minishell $> " CLOSE);
		if (ptr == NULL)
			return(-1);
		if (ft_strlen(ptr))
			add_history(ptr);
		if (open_quotes(ptr) < 0)
			printf("Minishell: Syntax error\n");
		else
		{
			mini.split_pipe  = ft_split_pipes(ptr);
			if (!mini.split_pipe)
			{
				mini.split_quote = ft_split_quotes(ptr);
				if (mini.split_quote[0][0] != -12)
				{
					dequoter(mini.split_quote);
					if (!ft_checkcom(mini.split_quote))
					{
						pid = fork();
						if (pid == 0)
						{
							checker(ptr2, mini.split_quote, &mini);
							exit (-1);
						}
						else
						{
							if (!ft_strncmp(ptr, "exit", 4))
								exit (-1);
							waitpid(pid, NULL, 0);
						}
					}
					else
						checker(ptr2, mini.split_quote, &mini);		
				}
				
			}
			else
			{
				ft_print(mini.split_pipe);
				mini.split_quote =ft_split_quotes(mini.split_pipe[0]);
				if (mini.split_quote[0][0] != -12)
				{
					pid = fork();
					if (pid == 0)
					{
						checker(ptr2, mini.split_quote, &mini);
						exit (-1);
					}
					else
					{
						if (!ft_strncmp(ptr, "exit", 4))
							exit (-1);
						waitpid(pid, NULL, 0);
					}
				}
				free(ptr);
			}
		}
	}
	ft_free_malloc2(mini.env);
	return (0);
}
