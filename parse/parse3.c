/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:51:23 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/15 04:57:14 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_is_space3(char c, int k)
{
	if (k == 1
		&& (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r'))
		return (0);
	return (1);
}

int	skip_aword(char const *s, int *i, int *k)
{
	if (s[*i] == '\2')
	{
		(*i)++;
		*k = 1;
	}
	while (!ft_is_space3(s[*i], *k))
	{
		(*i)++;
	}
	if (s[*i] == '\3')
	{
		*k = 0;
		(*i)++;
		return (1);
	}
	while (ft_is_space3(s[*i], *k) && s[*i])
	{
		if (s[*i] == '\2')
			*k = 1;
		if (s[*i] == '\3')
			*k = 0;
		(*i)++;
	}
	return (0);
}

void	exit_shell(void)
{
	printf("exit\n");
	exit(g_shell.ret);
}
