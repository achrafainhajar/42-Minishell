/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:01:04 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/16 03:14:38 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_parse *cmd, int is_piped)
{
	if (!cmd->argv[0])
	{
		if (!is_piped)
			printf("exit\n");
		exit(g_shell.ret);
	}
	else if (!str_digit(cmd->argv[0]))
	{
		printf("minishell: exit: %s : numeric argument required\n",
			cmd->argv[0]);
		exit(255);
	}
	else if (cmd->argv[1])
	{
		if (!is_piped)
			printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_shell.ret = 1;
	}
	else
	{
		if (!is_piped)
			printf("exit\n");
		exit(atol(cmd->argv[0]) % 256);
	}
}
