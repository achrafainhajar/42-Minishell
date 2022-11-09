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
}
