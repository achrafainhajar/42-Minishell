/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:40:52 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/15 04:44:11 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalphanum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_')
			i++;
		else
			return (1);
	}
	if (str[0] == '\0')
		return (1);
	return (0);
}

void	ft_errors(char *str, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" No such file or directory", 2);
		ft_putchar_fd('\n', 2);
		g_shell.ret = 1;
	}
}

void	normal_cmd(t_parse	*cmd, char	**env)
{
	char	*path;

	path = getpath(cmd->cmd, env);
	execute(path, cmd->argv, cmd->cmd, env);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i != n)
		return (str1[i] - str2[i]);
	return (0);
}
