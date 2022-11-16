/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:11:13 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/16 02:50:28 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parse	*add_command(t_parse *commad)
{
	t_parse	*new;

	new = init_command();
	commad = lst_add_back_command(commad, new);
	return (commad);
}

t_redir	*init_redir(char *val, int type, int type2, int exp)
{
	t_redir	*redir;

	redir = (t_redir *)f_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(val);
	redir->next = NULL;
	redir->e_type = type;
	if (exp)
		redir->mik = 1;
	else
		redir->mik = 0;
	if (g_shell.err != 0)
		redir->error = 1;
	else
		redir->error = type2;
	return (redir);
}

t_redir	*lst_add_back_redir(t_redir *lst, t_redir *new)
{
	t_redir	*tmp;

	if (!lst)
		return (new);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (lst);
}

t_redir	*add_redir(t_redir *redir, t_redir *new)
{
	redir = lst_add_back_redir(redir, new);
	return (redir);
}

char	*my_getenv_key(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}
