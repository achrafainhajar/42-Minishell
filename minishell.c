/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/11/15 04:58:25 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_tokens(t_token *tokens)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = ft_init_lexer(g_shell.line, g_shell.line[0]);
	tokens = send_lexer_to_tokenize(lexer);
	return (tokens);
}

void	init_gs(void)
{
	g_shell.line = NULL;
	g_shell.here_sig = 0;
	g_shell.err = 0;
	g_shell.mik = 0;
}

void	free_address(void)
{
	int	i;

	i = 0;
	while (g_shell.address[i] && i < g_shell.i)
	{
		free(g_shell.address[i]);
		g_shell.address[i] = NULL;
		i++;
	}
	g_shell.i = 0;
}

void	free_env(void)
{
	t_env	*tmp;

	while (g_shell.ev)
	{
		free(g_shell.ev->key);
		free(g_shell.ev->val);
		g_shell.ev->key = NULL;
		g_shell.ev->val = NULL;
		tmp = g_shell.ev;
		g_shell.ev = g_shell.ev->next;
		free(tmp);
	}
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*commands;
	t_token	*tokens;

	commands = NULL;
	tokens = NULL;
	(void)ac;
	(void)av;
	init_env(env);
	c_signal();
	while (1)
	{
		init_gs();
		g_shell.line = readline("mino-1.0$ ");
		if (!g_shell.line)
			exit_shell();
		if (only_enter())
			continue ;
		commands = init_command();
		tokens = create_tokens(tokens);
		create_commands(tokens, &commands);
		add_history(g_shell.line);
		minishell(commands);
		free_address();
		free(g_shell.line);
	}
	free_env();
}
