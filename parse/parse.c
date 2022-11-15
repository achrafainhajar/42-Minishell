/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:14:18 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:52:10 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_expantion2(t_token *token)
{
	if (token && token->flag != 1 && token->e_type == DOLLAR)
		return (1);
	else
	{
		while (token && token->flag == 1)
		{
			if (token->e_type != DOLLAR)
				return (0);
			token = token->next;
		}
	}
	return (1);
}

void	check_file_error(t_parse *command, char *value, int type, t_token *tmp)
{
	if (check_expantion(tmp) && (!ft_split2(value)[0]
		|| !ft_split2(value)[0][0] || ft_split2(value)[1]))
	{
		if (command->error == 0)
		{
			ft_putstr_fd("minishell: ambiguis redirection\n", 2);
			command->error = 1;
		}
		if (!command->redir)
			command->redir = init_redir(value, type, 1);
		else
			command->redir = add_redir(command->redir, value, type, 1);
	}
	else
	{
		if (check_expantion(tmp))
			value = ft_strdup(ft_split2(value)[0]);
		if (!command->redir)
			command->redir = init_redir(value, type, 0);
		else
			command->redir = add_redir(command->redir, value, type, 0);
	}
}

void	parse_helper(t_token **token, t_parse *command, char *value, int type)
{
	int			exec;
	t_token		*tmp;

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
		tmp = *token;
		value = jme3arg(token, exec, 1, 1);
		check_file_error(command, value, type, tmp);
	}
}

void	parse_commands(t_token **token, t_parse *command)
{
	char	*value;
	t_token	*tmp;

	value = NULL;
	if ((*token)->e_type == WORD || (*token)->e_type == DQUOTE
		|| (*token)->e_type == SQUOTE || (*token)->e_type == DOLLAR)
	{
		tmp = *token;
		value = jme3arg(token, 1, 2, 1);
		if (check_expantion(tmp))
			split_expansion(value, command);
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
			if (syntax_error(token))
				return ;
			head = add_command(head);
			head = head->next;
			token = token->next;
		}
	}
}
