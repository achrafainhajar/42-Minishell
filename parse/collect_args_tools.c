/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_args_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 01:39:50 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:51:18 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checkin_dollar(t_token **b, char **str, int ch_d)
{
	if (((*b)->next->e_type == DQUOTE || (*b)->next->e_type == SQUOTE)
		&& (*b)->val[1] != '?' && (*b)->val[1] != '$')
		(*b) = (*b)->next;
	else
	{
		if ((*b)->val[1] || (ch_d == 2 && !ft_isalnum((*b)->next->val[0])
				&& (*b)->next->val[0] != '_' ))
			*str = ft_strjoin(*str, dollar_q_d(b), f_malloc);
		else
		{
			(*b) = (*b)->next;
			(*b)->val = check_sp_chr(*b);
		}
	}
}

char	*dollar_q_d(t_token **b)
{
	char	*str;

	str = ft_strdup("");
	if ((*b)->val[1] == ' ' || (*b)->val[1] == '\0')
		str = ft_strjoin(str, ft_strdup("$"), f_malloc);
	else if ((*b)->val[1] == '?')
		str = ft_strjoin(str, ft_itoa(g_shell.ret), f_malloc);
	else if ((*b)->val[1] == '$')
		str = ft_strjoin(str, ft_strdup("$$"), f_malloc);
	return (str);
}

char	*normal_expansion(t_token **b, int f)
{
	t_token	*tmp;

	tmp = (*b);
	if (f)
		(*b) = (*b)->next;
	if (tmp->e_type == DOLLAR && tmp->val[1] == '\0')
		tmp->val = ft_strdup("$");
	else if (my_getenv(g_shell.ev, (*b)->val))
		(*b)->val = my_getenv(g_shell.ev, (*b)->val);
	else
		(*b)->val = ft_strdup("");
	return ((*b)->val);
}

char	*norm_sp(t_token *b, char *tmp)
{
	tmp = ((b)->val) + 1;
	(b)->val = ft_strdup("minishell");
	(b)->val = ft_strjoin((b)->val, tmp, f_malloc);
	return (b->val);
}

char	*check_sp_chr(t_token *b)
{
	char	**tmp;

	tmp = (char **) f_malloc(2 * sizeof(char *));
	if ((b)->val[str_sp_chr((b)->val)] != '\0'
		&& ((b)->val)[0] != '0')
	{
		tmp[0] = ft_substr((b)->val, 0, str_sp_chr((b)->val));
		tmp[1] = ft_substr((b)->val, str_sp_chr((b)->val),
				ft_int_strchr((b)->val, '\0'));
		if (my_getenv(g_shell.ev, tmp[0]))
			(b)->val = ft_strdup(my_getenv(g_shell.ev,
						tmp[0]));
		else
			(b)->val = ft_strdup("");
		if (tmp[1][0] == '\\')
			tmp[1]++;
		(b)->val = ft_strjoin((b)->val, tmp[1], f_malloc);
	}
	else if (((b)->val)[0] == '0')
		b->val = norm_sp(b, tmp[1]);
	else
		(b)->val = normal_expansion(&b, 0);
	return ((b)->val);
}
