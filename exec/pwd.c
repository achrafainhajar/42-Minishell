/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:14:15 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 23:14:15 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
		g_shell.ret = 0;
	}
	else
	{
		ft_putstr_fd("pwd: cannot get working directory\n", 2);
		g_shell.ret = 1;
	}
	free(str);
}

void	update_pwd(t_env **env, t_env *head, char *tmp)
{
	while (head)
	{
		if (ft_strcmp(head->key, "OLDPWD") == 0)
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
		if (tmp)
			free(tmp);
	}
}
