/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:59:33 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 17:52:33 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef  MINISHELL
#   define  MINISHELL

#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "libftt/libft.h"
#include <string.h>

int g_error;

typedef struct s_env
{
    char *str;
    struct s_env *next;
}       t_env;

typedef struct s_mini
{
    int pid_id;
    char **env;
    char    **split_pipe;
    char    **split_quote;
    t_env *env_new;
    int env_len;
}   t_mini ;


int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_free_malloc2(char **src);
char **ft_malloc(char **src, t_mini *mini);
void	ft_freeall(t_mini *mini);
int     open_quotes(char *str);
char	**ft_split_pipes(char *str);
char	**ft_split_quotes(char *str);
void	dequoter(char **mtrx);
char	**ft_getpath(char **env);
static int	ft_len_ptr(char *s, char c);
static int	ft_res_word(char *s, int len, int i, char **ptr);
static int	ft_get_word(char *s, char c, char **ptr, int ptrlen);
static char	**ft_res_pointer(int ptr);
char	**ft_splitraro(char const *s, char c);
void sighandler3(int signum);
void sighandler_quit(int signum);
void sighandler(int signum);
int	ft_get_size(char **str);
void	ft_putstr2(char *str, char **path);
int	ft_get_command(char **argcc, char **env);
void	ft_exit(int num);
void	ft_putstr(char *str);
int checker_inpipe(char **paths, char **src, t_mini *mini);
int	ft_lastpipe(char **cmd, int *first_pipe, t_mini *mini);
int	ft_firstpipes(char **cmd, int *first_pipe, t_mini *mini);
int	ft_pipes(t_mini *mini);
void	ft_env(t_mini *mini);
int	ft_echo(char **src, t_mini *mini);
void	ft_export(char **src, t_mini *mini);
int		ft_cd(char **str, t_mini *mini);
void	ft_printpwd(void);
int	ft_matrix_len(char **ptr);
char	*ft_pwd(void);
int	ft_echo(char **src, t_mini *mini);
int		ft_cd(char **str, t_mini *mini);
int	ft_check_var(char *src, t_mini *mini);
int	ft_check_var2(char *src);
char	*ft_gethome(t_mini *mini);
int	ft_strlen_export(char *env);
void	ft_export(char **src, t_mini *mini);
void	ft_unset(char **src, t_mini *mini);
void	ft_env(t_mini *mini);
int	ft_checkcom(char **src);
int checker(char **paths, char **src, t_mini *mini);



#endif
