/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:14:39 by ibaines           #+#    #+#             */
/*   Updated: 2023/01/02 19:48:27 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stddef.h>
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#define BOLD	"\001\033[1m\002"
#define CLOSE	"\001\033[0m\002"
#include <signal.h> 



int	ft_matrix_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

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

void	ft_putstr(char *str)
{	
	while (*(str) != '\0')
	{	
		write(2, str, 1);
		str = str + 1;
	}
}



int	main(int argc, char **argv, char **env)
{
	char		*ptr;
	char		**ptr2;
	char		**splited_argv;
	t_mini 		mini;
	int			i;
	int			status;
	int			pid; ///

   	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler_quit);
	signal(SIGABRT, sighandler);
	mini.env = ft_malloc(env, &mini);
	i = 0;
 	g_error = 0;
	i = 0;
	mini.split_pipe = NULL;
	mini.split_quote = NULL;
	ptr2 = ft_getpath(env);
	argv[1] = NULL;
	i = argc;
	i = 0;
	while (1) // separar comandos que hace el padre a los hijos
	{
		ptr = readline(BOLD "Minishell $> " CLOSE);
		if (ptr == NULL) //todo: llamar a una funcion para liberar todo lo que haya, ctrl + d
			ft_freeall(&mini);
		if (ft_strlen(ptr))
			add_history(ptr);
		if (open_quotes(ptr) < 0)
			printf("Minishell: Syntax error\n");
		else if (ft_strlen(ptr) > 0)
		{
			mini.split_pipe  = ft_split_pipes(ptr);
			if (mini.split_pipe[0][0] != -12)
			{
				if (!mini.split_pipe[1])
				{
					mini.split_quote = ft_split_quotes(ptr);
					mini.split_quote = dolar_expand(mini.split_quote, mini.env);
					if (mini.split_quote[0][0] != -12)
					{
						dequoter(mini.split_quote);
						ft_free_malloc2(mini.split_pipe);
						mini.split_pipe = NULL;
						free(ptr);
						if (!ft_checkcom(mini.split_quote))//comandos que puede hacer el hijo
						{
							pid = fork();
							if (pid == 0)
							{
								checker(ptr2, mini.split_quote, &mini);
								exit (-1);
							}
							else
							{
								if (WIFEXITED(status))
									g_error = WEXITSTATUS(status);
								//if (!ft_strncmp(mini.split_quote[0], "exit", 4))
								//	exit (-1);
								waitpid(pid, &status, 0);
								if (mini.split_quote)
								{
									ft_free_malloc2(mini.split_quote);
									mini.split_quote = NULL;
								}
							}
						}
						else //comandos que necesitan padre
						{
							checker(ptr2, mini.split_quote, &mini);	
							if (mini.split_quote)
							{
								ft_free_malloc2(mini.split_quote);
								mini.split_quote = NULL;
							}
						}
					}	
				}
				else
				{
					mini.split_quote = ft_split_quotes(mini.split_pipe[0]);
					mini.split_quote = dolar_expand(mini.split_quote, mini.env);
					dequoter(mini.split_quote);
					if (mini.split_quote[0][0] != -12)
						ft_pipes(&mini);
					free(ptr);
				}
			}
		}
		printf("exit = %d\n", g_error);
	}
	ft_free_malloc2(mini.env);
	return (0);
}
