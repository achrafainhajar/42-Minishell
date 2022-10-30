/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:45:32 by fahd              #+#    #+#             */
/*   Updated: 2022/10/30 21:43:08 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(void)
{
	printf("exit\n");
	exit(g_shell.ret);
}

t_token	*create_tokens(t_token *tokens)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = ft_init_lexer(g_shell.line, g_shell.line[0]);
	tokens = send_lexer_to_tokenize(lexer);
	return (tokens);
}

void	init_gs_and_c_signal(void)
{
	g_shell.line = NULL;
	g_shell.here_sig = 0;
	g_shell.err = 0;
	g_shell.mik = 0;
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*commands;
	t_token	*tokens;

	commands = NULL;
	tokens = NULL;
	(void)ac;
	(void)av;
	g_shell.i = 0;
	g_shell.ret = 0;
	init_env(env);
	c_signal();
	while (1)
	{
		g_shell.pid = 0;
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
		free(g_shell.line);
	}
}
