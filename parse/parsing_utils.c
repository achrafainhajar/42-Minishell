/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:24:32 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:52:34 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_int_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	if (s[i] == '\0')
		return (-1);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (!s[i])
		return (i);
	if ((char)c == '\0')
		return (i);
	return (-1);
}

int	token_index(char *str)
{
	char	*tokens;
	int		i;
	int		j;

	tokens = "$><|'\"";
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (tokens[j])
		{
			if (str[i] == tokens[j] || !ft_is_space(str[i]))
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_token(char c)
{
	char	*tokens;
	int		j;

	tokens = "$><|'\"";
	j = 0;
	while (tokens[j])
	{
		if (c == tokens[j] || !ft_is_space(c))
			return (1);
		j++;
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start || len == 0)
		return (ft_strdup(""));
	str = (char *)f_malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		if (j < len && i >= start)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	errors(int exitt)
{
	if (exitt == 2)
	{
		ft_putstr_fd("Minishell : unclosed quote!", 2);
		ft_putchar_fd('\n', 2);
		g_shell.err = 1;
		g_shell.ret = 2;
	}
	else if (exitt == 258)
	{
		ft_putstr_fd("Minishell : syntax error near unexpected token", 2);
		ft_putchar_fd('\n', 2);
		g_shell.err = 1;
		g_shell.ret = 258;
	}
	else if (exitt == 3)
	{
		ft_putstr_fd("Minishell : pipe open!", 2);
		ft_putchar_fd('\n', 2);
		g_shell.err = 1;
		g_shell.ret = 2;
	}
}
