/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:56:26 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 13:00:27 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void sighandler3(int signum)
{
	char c;

	c = 127;

	if (signum == SIGINT)
   {  
		write(1, "^C\n", 3);
		rl_replace_line("", 1);
		rl_redisplay();
}
}

void sighandler_quit(int signum)
{

	if (signum == SIGQUIT)
   {  
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
}
}

void sighandler(int signum)
{
	char c;

	c = 127;

	if (signum == SIGINT)
   {  
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
}
}