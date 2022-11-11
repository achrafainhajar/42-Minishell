/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:57:18 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 22:57:18 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	wrong_cmd(char *cmd)
{
	write(2, "mino: ", 7);
	write(2, cmd, ft_strlen(cmd));
	if (opendir(cmd) != NULL)
		ft_putstr_fd(": is a directory\n", 2);
	else if (ft_strchr(cmd, '/') && access(cmd, F_OK) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (ft_strchr(cmd, '/') && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(": permission denied\n", 2);
		exit(126);
	}
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

char	*ft_strjoine(char *s1, char *s2)
{
	int		i;
	char	*str;
	int		b;

	if (!s1 || !s2)
		return (0);
	str = f_malloc(sizeof(char) * (strlen(s1) + strlen(s2)) + 2);
	if (!str)
		return (NULL);
	i = 0;
	b = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	if (*s1)
		str[i++] = '/';
	while (s2[b])
		str[i++] = s2[b++];
	str[i] = '\0';
	return (str);
}

void	execute(char *path, char **cmdargs, char *cmd, char **envp)
{
	if (cmd && cmdargs && envp && ft_strchr(cmd, '/'))
		execve(cmd, cmdargs, envp);
	if (access(path, F_OK) == 0)
	{
		if (execve(path, cmdargs, envp) == -1)
			wrong_cmd(path);
	}
	wrong_cmd(cmd);
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

char	*path_address(char **env)
{
	int		i;

	i = 0;
	while (env[i] && strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

char	*getpath(char	*cmd, char	**env)
{
	char	*path;
	char	*dir;
	char	*bin;

	dir = NULL;
	path = path_address(env);
	if (!path)
		return (cmd);
	while (cmd && cmd[0] != '\0' && cmd[0] != '.' && cmd[0] != '/'
		&& path && ft_int_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_int_strchr(path, ':'));
		bin = ft_strjoine(dir, cmd);
		if (access(bin, F_OK) == 0)
			return (bin);
		if (ft_int_strchr(path, ':') != ft_strlen(path))
			path += ft_int_strchr(path, ':') + 1;
		else
			break ;
	}
	if (dir && (ft_int_strchr(path, ':') == ft_strlen(path) || !path[0]))
		wrong_cmd(cmd);
	return (cmd);
}
