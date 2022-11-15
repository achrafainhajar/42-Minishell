/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 02:00:11 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:52:46 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	cpt;
	int	j;

	i = 0;
	cpt = 0;
	j = 1;
	while (s[i])
	{
		if (s[i] == c)
			j = 1;
		else if (j == 1)
		{
			j = 0;
			cpt++;
		}
		i++;
	}
	return (cpt);
}

static int	ft_charcount(const char *s, char c, int i)
{
	int	cnt;

	cnt = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static char	**ft_splitcpy(const char *s, char c, char **str, int wd)
{
	int	i;	
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] && wd > cnt)
	{
		j = 0;
		while (s[i] == c)
			i++;
		str[cnt] = f_malloc(sizeof(char ) * ft_charcount(s, c, i) + 1);
		if (!str[cnt])
			return (NULL);
		while (s[i] != c && s[i])
		{
			str[cnt][j] = s[i];
			i++;
			j++;
		}
		str[cnt][j] = '\0';
		cnt++;
	}
	str[cnt] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		wd;
	char	**str;

	if (!s)
		return (0);
	wd = ft_words(s, c);
	str = f_malloc(sizeof(char *) * (wd + 1));
	if (str == NULL)
		return (0);
	return (ft_splitcpy(s, c, str, wd));
}
