#   ifndef  MINISHELL
#   define  MINISHELL

#include <stddef.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "libftt/libft.h"

int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_free_malloc2(char **src);
int     open_quotes(char *str);
char	**ft_split_pipes(char *str);
char	**ft_split_quotes(char *str);

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


#endif
