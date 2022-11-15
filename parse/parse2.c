/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:57:54 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 04:52:02 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_words(char const *s)
{
	int	i;
	int	cpt;
	int	k;

	i = 0;
	k = 0;
	cpt = 0;
	while (s[i])
	{
		if (skip_aword(s, &i, &k))
			continue ;
		cpt++;
	}
	return (cpt);
}

static int	ft_charcount(const char *s, int i, int k)
{
	int	cnt;

	cnt = 0;
	while (s[i] && ft_is_space3(s[i], k))
	{
		if (s[i] == '\2')
			k = 1;
		if (s[i] == '\3')
			k = 0;
		i++;
		cnt++;
	}
	return (cnt);
}

static char	*ft_cpy(const char *s, int *i, int *k, int j)
{
	char	*str;

	str = f_malloc(sizeof(char) * ft_charcount(s, *i, *k) + 1);
	if (!str)
		return (NULL);
	while (ft_is_space3(s[*i], *k) && s[*i])
	{
		if (s[*i] == '\002')
		{
			(*i)++;
			*k = 1;
			continue ;
		}
		if (s[*i] == '\003')
		{
			(*i)++;
			*k = 0;
			continue ;
		}
		str[j] = s[*i];
		(*i)++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	**ft_splitcpy(const char *s, char **str, int wd)
{
	int		i;
	int		j;
	int		cnt;
	int		k;

	k = 0;
	i = 0;
	cnt = 0;
	while (s[i] && wd > cnt)
	{
		j = 0;
		if (s[i] == '\2')
		{
			i++;
			k = 1;
		}
		while (!ft_is_space3(s[i], k))
			i++;
		str[cnt] = ft_cpy(s, &i, &k, j);
		cnt++;
	}
	str[cnt] = NULL;
	return (str);
}

char	**ft_split2(char const *s)
{
	int		wd;
	char	**str;

	if (!s)
		return (0);
	wd = ft_words(s);
	str = f_malloc(sizeof(char *) * (wd + 1));
	if (str == NULL)
		return (0);
	return (ft_splitcpy(s, str, wd));
}
