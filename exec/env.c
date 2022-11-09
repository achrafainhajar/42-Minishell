/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:56:03 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 22:56:03 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	ft_env(t_env *env, t_parse *cmd)
{
	if (!cmd->argv[0])
	{
		while (env)
		{
			if (env->sep)
			{
				ft_putstr_fd(env->key, 1);
				ft_putchar_fd(env->sep, 1);
				ft_putstr_fd(env->val, 1);
				ft_putchar_fd('\n', 1);
			}
			env = env->next;
		}
		g_shell.ret = 0;
	}
	else
	{
		ft_putstr_fd("Too many arguments\n", 2);
		g_shell.ret = 127;
	}
}
