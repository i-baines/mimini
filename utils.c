/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaines <ibaines@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:04:48 by ibaines           #+#    #+#             */
/*   Updated: 2022/12/30 13:04:49 by ibaines          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i ++;
			while (str[i] == ' ')
				i ++;
		}
		if (!str[i])
			return (0);
		i ++;
	}
	return (1);
}

int	open_pipes(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i ++;
	if (i > 0 && (str[0] == '|' || str[i - 1] == '|'))
		return (0);
	i = 0;
	if (str[i] == ' ')
	{
		while (str[i] == ' ')
		{
			i ++;
			if (str[i] == '|')
				return (0);
		}
	}
	if (!open_pipes2(str))
		return (0);
	return (1);
}

int	open_quotes(char *str)
{
	int		check;
	char	quote;

	check = 1;
	quote = 'x';
	if (!open_pipes(str))
		return (-1);
	while (*str)
	{
		if (*str == '\'' && quote != 'd')
		{
			quote = 's';
			check = check * -1;
		}
		else if (*str == '\"' && quote != 's')
		{
			quote = 'd';
			check = check * -1;
		}
		if (check == 1)
			quote = 'x';
		str++;
	}
	return (check);
}

void	change_caracter(char *str, char caracter)
{
	int		check;
	char	quote;

	check = 1;
	quote = 'x';
	while (*str)
	{
		if (*str == '\'' && quote != 'd')
		{
			quote = 's';
			check = check * -1;
		}
		else if (*str == '\"' && quote != 's')
		{
			quote = 'd';
			check = check * -1;
		}
		if (check == 1)
			quote = 'x';
		if (*str == caracter && quote == 'x')
			*str = caracter -128;
		str++;
	}
	return ;
}

void	ft_init_help(t_help *v)
{
	v->pipes = 0;
	v->check = 1;
	v->quote = 'x';
}

int	change_caracter2(char *str)
{
	t_help	v;

	ft_init_help(&v);
	while (*str++)
	{
		if (*(str - 1) == '\'' && v.quote != 'd')
		{
			v.quote = 's';
			v.check = v.check * -1;
		}
		else if (*(str - 1) == '\"' && v.quote != 's')
		{
			v.quote = 'd';
			v.check = v.check * -1;
		}
		if (v.check == 1)
			v.quote = 'x';
		if (*(str - 1) == ' ' && v.quote == 'x')
		{
			v.pipes ++;
			*(str - 1) = ' ' -128;
		}
	}
	return (v.pipes);
}

int	change_caracter_q(char *str)
{
	t_help	v;

	v.num = 0;
	v.check = 1;
	v.quote = 'x';
	while (*str++)
	{
		if (*(str - 1) == '\'' && v.quote != 'd')
		{
			v.num ++;
			v.quote = 's';
			v.check = v.check * -1;
			*(str - 1) = -128;
		}
		else if (*(str - 1) == '\"' && v.quote != 's')
		{
			v.num ++;
			v.quote = 'd';
			v.check = v.check * -1;
			*(str - 1) = -128;
		}
		if (v.check == 1)
			v.quote = 'x';
	}
	return (v.num / 2);
}

int	check_mtrx_pipe(char **mtrx)
{
	t_help	v;

	v.word = 0;
	v.flag = 0;
	v.j = 0;
	v.i = 0;
	while (mtrx[v.i])
	{
		while (mtrx[v.i][v.j])
		{
			if (mtrx[v.i][v.j] > 32)
				v.flag = 1;
			v.j ++;
		}
		if (v.flag == 1)
			v.word ++;
		v.flag = 0;
		v.j = 0;
		v.i ++;
	}
	if (v.word == v.i)
		return (0);
	printf("Minishell: Syntax error\n");
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	**ft_free(char **d, size_t start)
{
	size_t	j;

	if (d)
	{
		j = 0;
		while (j < start)
		{
			if (d[j] != NULL)
				free(d[start]);
			start++;
		}
		free(d);
	}
	return (NULL);
}

size_t	ft_lines(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	if (s[i - 1] == c)
		count--;
	return (count);
}

size_t	ft_wc(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		count++;
	}
	return (count);
}

char	**ft_fill(char **dest, const char *s, char to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s != '\0')
	{
		while (*s == to_find && *s != '\0')
			s++;
		if (*s == '\0')
			continue ;
		dest[i] = malloc(sizeof(char) * ft_wc(s, to_find) + 1);
		if (dest[i] == NULL)
			return (ft_free(dest, i));
		j = 0;
		while (*s != to_find && *s != '\0')
		{
			dest[i][j] = *s;
			j++;
			s++;
		}
		dest[i][j] = '\0';
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!s)
		return (NULL);
	if (ft_strlen(s) > 0)
		dest = malloc(sizeof(char *) * (ft_lines(s, c) + 1));
	else
		dest = malloc(sizeof(char *) * (0 + 1));
	if (dest == NULL)
		return (NULL);
	ft_fill(dest, s, c);
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	ptr = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	while (n-- > 0)
		*(ptr++) = *(ptr2++);
	return (dest);
}

char	*ft_replace(char *str, char caracter)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = ft_strlen(str);
	dest = (char *)malloc(sizeof(char) * (i + 1));
	while (str[i])
	{
		if (str[i] != caracter)
		{
			dest[j] = str[i];
			j ++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	**ft_split_pipes(char *str)
{
	char	**splited_argv;
	char	*temp;

	temp = ft_strdup(str);
	change_caracter(temp, '|');
	splited_argv = ft_split(temp, '|' -128);
	if (check_mtrx_pipe(splited_argv))
	{
		free(temp);
		splited_argv[0][0] = -12;
		return (splited_argv);
	}
	free(temp);
	return (splited_argv);
}

char	**ft_split_quotes(char *str)
{
	int		caracter_value;
	char	**splited_argv;
	char	*new_str;

	caracter_value = change_caracter2(str);
	if (caracter_value > 0)
	{
		splited_argv = ft_split(str, ' ' -128);
		if (check_mtrx_pipe(splited_argv))
		{
			splited_argv[0][0] = -12;
			return (splited_argv);
		}
	}
	else
	{
		splited_argv = (char **)malloc(sizeof(char *) * 2);
		splited_argv[0] = ft_strdup(str);
		splited_argv[1] = NULL;
	}
	return (splited_argv);
}

char	*ft_join2(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, s1_len + 1);
	ft_strlcat(&dest[s1_len], s2, s2_len + 1);
	free((char *)s1);
	return (dest);
}

void	dequoter(char **mtrx)
{
	int		i;
	int		len;
	char	**temp;

	len = 0;
	i = 0;
	while (mtrx[i])
	{
		if (change_caracter_q(mtrx[i]))
		{
			temp = ft_split(mtrx[i], -128);
			mtrx[i][0] = '\0';
			while (temp[len])
			{
				mtrx[i] = ft_join2(mtrx[i], temp[len]);
				free(temp[len]);
				len ++;
			}
			free(temp);
			len = 0;
		}
		i ++;
	}
}
