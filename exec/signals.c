/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:21:06 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 23:21:06 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_helper(void)
{
	if (!g_shell.line)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		g_shell.ret = 1;
	}
	else
		ft_putchar_fd('\n', 0);
}

void	sig_child(int sig)
{
	if (sig == SIGINT)
	{
		if (g_shell.here_sig == 27)
		{
			g_shell.here_sig = -27;
			ft_putchar_fd('\n', 0);
			close(rl_instream->_fileno);
			g_shell.ret = 1;
			g_shell.err = 1;
		}
		else
			sig_helper();
	}
	else if (sig == SIGQUIT)
	{
		if (!g_shell.line)
		{
			ft_putchar_fd('\r', STDERR_FILENO);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	sig_handler(int sig)
{
	if (!kill(g_shell.pid, sig))
	{
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: \n", 1);
			g_shell.ret = 131;
		}
		else if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			g_shell.ret = 130;
		}
	}
	else
		sig_child(sig);
}

void	ctrls(int sig)
{
	if (g_shell.line && sig == SIGCHLD
		&& strcmp(g_shell.line, "./minishell") == 0)
		c_signal();
	if (g_shell.pid != 0)
		sig_handler(sig);
	else
		sig_child(sig);
}

void	c_signal(void)
{
	signal(SIGCHLD, ctrls);
	signal(SIGINT, ctrls);
	signal(SIGQUIT, ctrls);
}
