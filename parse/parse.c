/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:14:18 by fstitou           #+#    #+#             */
/*   Updated: 2022/11/06 13:27:19 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parse	*init_command(void)
{
	t_parse	*command;

	command = (t_parse *)f_malloc(sizeof(t_parse));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->argv = (char **)realloc_array(NULL, ft_strdup(""));
	command->redir = NULL;
	command->next = NULL;
	command->error = 0;
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

void	parse_helper(t_token **token, t_parse *command, char *value, int type)
{
	int	exec;

	exec = type;
	if ((*token)->next->e_type == END || (*token)->next->e_type == PIPE
		|| (*token)->next->e_type == GREAT || (*token)->next->e_type == LESS
		|| (*token)->next->e_type == LESSANDLESS
		|| (*token)->next->e_type == GREATANDGREAT)
	{
		if (g_shell.err == 0)
			errors(258);
		(*token) = (*token)->next;
	}
	else
	{
		type = (*token)->e_type;
		(*token) = (*token)->next;
		value = jme3arg(token, exec, 1);
		if (!command->redir)
			command->redir = init_redir(value, type);
		else
			command->redir = add_redir(command->redir, value, type);
	}
	
}

void	parse_commands(t_token **token, t_parse *command)
{
	char	*value;
	char	**split;
	t_token	*tmp;
	int 	i;

	value = NULL;
	if ((*token)->e_type == WORD || (*token)->e_type == DQUOTE
		|| (*token)->e_type == SQUOTE || (*token)->e_type == DOLLAR)
	{
		tmp = *token;
		value = jme3arg(token, 1, 1);
		if (tmp->e_type == DOLLAR)
		{
			i = 0;
			split = ft_split(value, ' ');
			if (!command->cmd)
				command->cmd = split[i++];
			while (split && split[i])
				command->argv = (char **)realloc_array(command->argv, split[i++]);
		}
		else if (!command->cmd)
			command->cmd = value;
		else
			command->argv = (char **)realloc_array(command->argv, value);
	}
	else if ((*token)->e_type == GREAT || (*token)->e_type == LESS
		|| (*token)->e_type == LESSANDLESS || (*token)->e_type == GREATANDGREAT)
	{
		if ((*token)->e_type == LESSANDLESS)
			parse_helper(token, command, value, 0);
		else
			parse_helper(token, command, value, 1);
	}
}

void	create_commands(t_token *token, t_parse **command)
{
	t_parse	*head;

	head = *command;
	if (token->e_type == PIPE)
	{
		errors(258);
		return ;
	}
	while (token)
	{
		parse_commands(&token, head);
		if (token->e_type == PIPE || token->e_type == END)
		{
			if (token->next && (token->next->e_type == END || token->next->e_type == PIPE))
			{
				if (token->next->e_type == END)
					errors(3);
				else if (token->next->e_type == PIPE)
					errors(258);
				return ;
			}
			head = add_command(head);
			head = head->next;
			if (g_shell.err != 0)
				head->error = 1;
			token = token->next;
		}
	}
}
