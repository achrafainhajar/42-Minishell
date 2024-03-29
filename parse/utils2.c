/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 02:06:10 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:53:20 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_ex_token(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

int	is_piped(void)
{
	int	i;

	i = 0;
	while (g_shell.line[i])
	{
		if (g_shell.line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

static long	ft_count(int n)
{
	long	i;
	long	j;

	j = (long)n;
	i = 0;
	if (j < 0)
	{
		i++;
		j *= -1;
	}
	while (j > 0)
	{
		j = j / 10;
		i++;
	}
	return (i);
}

static void	ft_intochar(char *str, long *i, long *k, long *j)
{
	while (*k != 0)
	{
		if ((*k) > 0)
		{
			str[(*i) - 1] = (*j) % 10 + '0';
			(*i)--;
			(*k) = (*k) / 10;
			(*j) = (*j) / 10;
		}
		if (*k < 0)
		{
			str[*i] = (*j) % 10 + '0';
			(*i)--;
			(*k) = (*k) / 10;
			(*j) = (*j) / 10;
		}
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	i;
	long	k;
	long	j;

	j = (long)n;
	k = j;
	i = ft_count(j);
	if (j == 0)
		return (ft_strdup("0"));
	str = (char *)f_malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	if (n < 0)
		i--;
	if (j < 0)
	{
		j *= -1;
		str[0] = '-';
		str[i + 1] = 0;
	}
	else
		str[i] = 0;
	ft_intochar(str, &i, &k, &j);
	return (str);
}
