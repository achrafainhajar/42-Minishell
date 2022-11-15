/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:11:14 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:51:11 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dollar_qu(t_token **b, int exec, char *str)
{
	(void)exec;
	if ((*b)->val[1] == '?')
		str = ft_strjoin(str, ft_itoa(g_shell.ret), f_malloc);
	else if ((*b)->val[1] == '\0')
		str = ft_strjoin(str, ft_strdup("$"), f_malloc);
	else if ((*b)->val[1] == '$')
		str = ft_strjoin(str, ft_strdup("$$"), f_malloc);
	(*b) = (*b)->next;
	return (str);
}

char	*check_end(t_token **b, char *str, int exec)
{
	if ((*b) && (*b)->e_type == DQUOTE)
	{
		str = ft_strjoin(str, expand_dollar((*b)->val, exec), f_malloc);
		(*b) = (*b)->next;
	}
	else if ((*b) && (*b)->e_type != END)
	{
		str = ft_strjoin(str, (*b)->val, f_malloc);
		(*b) = (*b)->next;
	}
	return (str);
}

int	jm3arg_join_simple(t_token **b, char **str, int exec)
{
	if ((*b)->e_type == DQUOTE)
		*str = ft_strjoin(*str, expand_dollar((*b)->val, exec), f_malloc);
	else if ((*b)->e_type != END && ((*b)->e_type
			!= DOLLAR || (!exec && (*b)->next->e_type
				!= SQUOTE && (*b)->next->e_type != DQUOTE)))
		*str = ft_strjoin(*str, (*b)->val, f_malloc);
	if ((*b)->flag == 1)
			(*b) = (*b)->next;
	else
	{
		(*b) = (*b)->next;
		return (1);
	}
	return (0);
}

void	check_redis(t_token *tmp)
{
	while (tmp && tmp->flag == 1 && tmp->e_type
		!= DQUOTE && tmp->e_type != SQUOTE)
		tmp = tmp->next;
	if (tmp && (tmp->e_type == DQUOTE || tmp->e_type == SQUOTE))
		g_shell.mik = 1;
}

char	*jme3arg(t_token **b, int exec, int ch_d, int exp)
{
	char	*str;

	str = ft_strdup("");
	if (!exec)
		check_redis(*b);
	while ((*b) && (*b)->flag == 1)
	{
		if ((*b)->e_type == DOLLAR && exec)
		{
			checkin_dollar(b, &str, ch_d);
			if (exp && (*b)->e_type != DQUOTE
				&& (*b)->e_type != SQUOTE)
			{
				(*b)->val = ft_strjoin("\2", (*b)->val, f_malloc);
				(*b)->val = ft_strjoin((*b)->val, "\3", f_malloc);
			}
		}
		if (jm3arg_join_simple(b, &str, exec))
			return (str);
	}
	if ((*b) && (*b)->e_type == DOLLAR && exec)
		return (normal_or_qu(b, exec, str));
	str = check_end(b, str, exec);
	return (str);
}
