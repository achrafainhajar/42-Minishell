/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:30:08 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/16 03:04:02 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_parse	*cmd)
{
	if (cmd->cmd && builtins_cases(cmd))
	{
		execute_builtins(cmd, &g_shell.ev, 1);
	}
	else if (cmd->cmd)
		normal_cmd(cmd, env_to_tab(&g_shell.ev));
}

void	child_f(t_parse *cmd, int *fd, int *fds)
{
	if (g_shell.pid == 0)
	{
		close(fd[0]);
		open_redir(cmd, fds, fd);
		if (!g_shell.err && !cmd->error)
			execution(cmd);
		exit(g_shell.ret);
	}
	else if (g_shell.pid != -1)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	ft_supervisor(int	*fds)
{
	int	i;

	i = 0;
	waitpid(g_shell.pid, &i, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(i))
		g_shell.ret = WEXITSTATUS(i);
	dup2(fds[1], 1);
	dup2(fds[0], 0);
}

void	child_p(t_parse *cmd, int *fd, int *fds)
{
	while (cmd)
	{
		if (cmd->cmd || cmd->redir)
		{
			pipe(fd);
			if (cmd->cmd && ft_strcmp(cmd->cmd, "./minishell") == 0)
			{
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
			}
			g_shell.pid = fork();
			if (g_shell.pid == -1)
				ft_putstr_fd("fork failed\n", 2);
			child_f(cmd, fd, fds);
		}
		cmd = cmd->next;
	}
}

void	minishell(t_parse	*cmd)
{
	int	fd[2];
	int	fds[2];

	fds[1] = dup(1);
	fds[0] = dup(0);
	ft_here_doc(cmd);
	if (g_shell.err != 0)
		return ;
	if (cmd && cmd->cmd && builtins_cases(cmd)
		&& (cmd->next && !cmd->next->cmd))
	{
		open_redir(cmd, fds, fd);
		if (!g_shell.err && !cmd->error)
			execute_builtins(cmd, &g_shell.ev, 0);
		dup2(fds[1], 1);
		dup2(fds[0], 0);
		return ;
	}
	child_p(cmd, fd, fds);
	ft_supervisor(fds);
}
