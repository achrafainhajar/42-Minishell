/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:01:04 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 23:01:50 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_parse *cmd)
{
	if (!cmd->argv[0])
	{
		printf("exit\n");
		exit(g_shell.ret);
	}
	else if (!str_digit(cmd->argv[0]))
	{
		printf("minishell: exit: ");
		printf("%s ", cmd->argv[0]);
		printf(": numeric argument required\n");
		exit(2);
	}
	else if (cmd->argv[1])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_shell.ret = 1;
	}
	else
	{
		printf("exit\n");
		exit(atol(cmd->argv[0]) % 256);
	}
}
