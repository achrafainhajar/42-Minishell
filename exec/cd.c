/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:41:42 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 22:41:42 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	new_paths(t_env **env)
{
	t_env	*head;
	char	*tmp;

	head = (*env);
	while (head)
	{
		if (strcmp(head->key, "PWD") == 0)
		{
			tmp = head->val;
			head->val = getcwd(NULL, 0);
			break ;
		}
		head = head->next;
	}
	head = (*env);
	while (head)
	{
		if (strcmp(head->key, "OLDPWD") == 0)
		{
			free(head->val);
			head->val = tmp;
			break ;
		}
		head = head->next;
	}
	if (!head)
	{
		fill_export("OLDPWD", tmp, env, 1);
		free(tmp);
	}
}

void	ft_home(void)
{
	char	*home;

	home = my_getenv(g_shell.ev, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_shell.ret = 1;
	}
	else if (!chdir(home))
	{
		new_paths(&g_shell.ev);
		g_shell.ret = 0;
	}
}

void	ft_minus(t_env **env)
{
	if (!chdir(my_getenv(g_shell.ev, "OLDPWD")))
	{
		new_paths(env);
		ft_putstr_fd(my_getenv(*env, "PWD"), 1);
		ft_putchar_fd('\n', 1);
		g_shell.ret = 0;
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(my_getenv(*env, "OLDPWD"), 2);
		if (my_getenv(*env, "OLDPWD"))
			ft_putstr_fd(" No such file or directory", 2);
		else
			ft_putstr_fd("OLDPWD not set", 2);
		ft_putchar_fd('\n', 2);
		g_shell.ret = 1;
	}
}

void	cd_tilde(char	*path)
{
	char	*dir;

	ft_home();
	if (g_shell.ret != 1 && ft_strcmp(path, "~") != 0)
	{
		dir = strchr(path, '/');
		if (dir)
		{
			dir++;
			if (chdir(dir) != 0)
				ft_errors(path, 1);
			else
			{
				new_paths(&g_shell.ev);
				g_shell.ret = 0;
			}
		}
		else
			ft_errors(path, 1);
	}
}

void	ft_cd(t_parse *cmd, t_env **env)
{
	char	*tmp;

	if (cmd->argv[0] && cmd->argv[1] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		ft_putchar_fd('\n', 2);
		g_shell.ret = 1;
	}
	else if (!cmd->argv[0])
		ft_home();
	else if (cmd->argv[0][0] == '~')
		cd_tilde(cmd->argv[0]);
	else if (!strcmp(cmd->argv[0], "-"))
		ft_minus(env);
	else if (!chdir(cmd->argv[0]))
	{
		tmp = getcwd(NULL, 0);
		if (tmp)
			new_paths(env);
		else
			ft_putstr_fd("cd: error retrieving current directory\n", 2);
		free (tmp);
	}
	else if (cmd->argv[0][0] != '\0')
		ft_errors(cmd->argv[0], 1);
}
