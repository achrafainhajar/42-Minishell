/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:49:02 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/15 04:50:57 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (0);
	return (1);
}

char	*normal_or_qu(t_token **b, int exec, char *str)
{
	if (!(*b)->val[1] && (*b)->next && (*b)->next->flag == 1)
		return (normal_expansion(b, 1));
	else
		return (dollar_qu(b, exec, str));
}

t_parse	*init_command(void)
{
	t_parse	*command;

	command = (t_parse *)f_malloc(sizeof(t_parse));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->argv = (char **)realloc_array(NULL, ft_strdup(""));
	command->redir = NULL;
	command->error = 0;
	command->next = NULL;
	return (command);
}

t_parse	*lst_add_back_command(t_parse *lst, t_parse *new)
{
	t_parse	*tmp;

	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

int	check_expantion(t_token *token)
{
	if (token && token->flag != 1 && token->e_type == DOLLAR)
		return (1);
	else
	{
		while (token && token->flag == 1)
		{
			if (token->e_type == DOLLAR && token->next->e_type
				!= SQUOTE && token->next->e_type != DQUOTE)
				return (1);
			token = token->next;
		}
	}
	return (0);
}
