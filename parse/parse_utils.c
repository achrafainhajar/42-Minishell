/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:11:13 by fahd              #+#    #+#             */
/*   Updated: 2022/11/07 16:02:16 by hlachkar         ###   ########.fr       */
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

t_redir	*init_redir(char *val, int type)
{
	t_redir	*redir;

	redir = (t_redir *)f_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = ft_strdup(val);
	redir->next = NULL;
	redir->e_type = type;
	if (g_shell.err != 0)
		redir->error = 1;
	else
		redir->error = 0;
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

t_redir	*add_redir(t_redir *redir, char *val, int type)
{
	t_redir	*new;

	new = init_redir(val, type);
	redir = lst_add_back_redir(redir, new);
	return (redir);
}

char	*my_getenv_key(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}
