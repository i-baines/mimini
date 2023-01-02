#include "minishell.h"

int	pid = 145986;

void	add_pid(char *dst, char *pid, int len)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (dst[pos])
		pos ++;
	while (i < len)
	{
		dst[pos] = pid[i];
		i ++;
		pos ++;
	}
}

void	add_final(char *dst, char *str, int pos)
{
	int	i;

	i = ft_strlen(dst);
	while (str[pos])
	{
		dst[i] = str[pos];
		i ++;
		pos ++;
	}
	dst[i] = '\0';
}

char	*expand_pid(char *str, int pos)
{
	int		pid_len;
	char	*pid2;
	char	*temp;

	pid2 = ft_itoa(pid);
	pid_len = ft_strlen(pid2);
	temp = malloc(ft_strlen(str) + pid_len + 1);
	ft_strlcpy(temp, str, pos + 1);
	ft_strlcat(temp, pid2, pid_len + ft_strlen(temp) + 1);
	add_final(temp, str, pos + 2);
	free(pid2);
	free(str);
	return (temp);
}

char	*expand_error(char *str, int pos)
{
	int		error_len;
	char	*error2;
	char	*temp;

	error2 = ft_itoa(g_error);

	error_len = ft_strlen(error2);
	temp = (char *)malloc(ft_strlen(str) + error_len + 1);
	ft_strlcpy(temp, str, pos + 1);
	ft_strlcat(temp, error2, error_len + ft_strlen(temp) + 1);
	add_final(temp, str, pos + 2);
	if (error_len == 1)
		temp[pos + 2] = '\0';
	free(error2);
	free(str);
	return (temp);
}

int	check_expansion(char *name, char **env)
{
	int		i;
	char	c;

	i = 0;
	while (env[i])
	{
		c = env[i][ft_strlen(name)];
		if (!ft_strncmp(name, env[i], ft_strlen(name)) && c == '=')
			return (i);
		i ++;
	}
	return (0);
}

char	*find_word(char *str, int i)
{
	char	*dst;
	int		j;
	int		word_len;
	int		pos;

	j = 0;
	pos = i;
	word_len = 0;
	while (ft_isalnum(str[i + 1]))
	{
		i ++;
		word_len ++;
	}
	dst = malloc(word_len + 1);
	dst[0] = '\0';
	i = pos;
	while (ft_isalnum(str[i + 1]))
	{
		dst[j] = str[i + 1];
		i ++;
		j ++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*find_value(char *env)
{
	int		start;
	int		end;
	char	*value;
	int		i;

	i = 0;
	start = 0;
	end = 0;
	while (env[start] != '=')
		start ++;
	while (env[end])
		end ++;
	value = malloc(end - start);
	start += 1;
	while (start < end)
	{
		value[i] = env[start];
		start ++;
		i ++;
	}
	value[i] = '\0';
	return (value);
}

char	*expanding(char *str, char *word, char *env, int pos)
{
	char	*value;
	char	*dst;

	value = find_value(env);
	dst = malloc(ft_strlen(str) + ft_strlen(value) + 1);
	ft_strlcpy(dst, str, pos + 1);
	ft_strlcat(dst, value, ft_strlen(value) + ft_strlen(dst) + 1);
	add_final(dst, str, pos + ft_strlen(word) + 1);
	free(value);
	free(str);
	return (dst);
}

char	*expand_delete(char *str, char *word, int pos)
{
	char	*dst;

	dst = malloc(ft_strlen(str) + 1);
	dst[0] = '\0';
	ft_strlcpy(dst, str, pos + 1);
	dst[pos + 1] = '\0';
	add_final(dst, str, pos + ft_strlen(word) + 1);
	free(str);
	return (dst);
}

char	*expand(char *str, int i, char **env)
{
	char	*word;
	int		line;

	word = find_word(str, i);
	line = check_expansion(word, env);
	if (line)
		str = expanding(str, word, env[line], i);
	else
		str = expand_delete(str, word, i);
	free(word);
	return (str);
}

char	*expand_loop(int i, char *str, char **env)
{
	while (str[i] == '$' && str[i + 1])
	{
		if (str[i + 1] != '$')
		{
			if (str[i + 1] == '?')
			{
				str = expand_error(str, i);
				i ++;
			}
			else
			{
				str = expand(str, i, env);
				break ;
			}
			i ++;
		}
	}
	return (str);
}

char	*dolar_expand_str(char *str, char **env)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
		return (str);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] > 32 && str[i + 1] != 34)
		{
			if (str[i + 1] && str[i + 1] == '$')
				str = expand_pid(str, i);
			else
				str = expand_loop(i, str, env);
			i = 0;
		}
		i ++;
	}
	return (str);
}

char	**dolar_expand(char **mtrx, char **env)
{
	int	i;

	i = 0;
	while (mtrx[i])
	{
		mtrx[i] = dolar_expand_str(mtrx[i], env);
		i ++;
	}
	return (mtrx);
}