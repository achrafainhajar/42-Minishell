#include "../minishell.h"
void wrong_cmd(char *cmd)
{
	write(2, "mino: ", 7);
	write(2, cmd, ft_strlen(cmd));
	if ((cmd[0] == '.' || cmd[0] == '/') && access(cmd, F_OK) == -1)
		write(2, ": No such file or directory\n", 29);
	else if ((cmd[0] == '.' || cmd[0] == '/') && access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(": permission denied\n", 2);
		exit (126);
	}
	else
		write(2, ": command not found\n", 20);
	exit(127);
}
char *ft_strjoine(char *s1, char *s2)
{
	int i;
	char *str;
	int b;

	if (!s1 || !s2)
		return (0);
	str = malloc(sizeof(char) * (strlen(s1) + strlen(s2)) + 2);
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
	{
		str[i] = s2[b];
		i++;
		b++;
	}
	str[i] = '\0';
	return (str);
}

void execute(char *path, char **cmdargs, char *cmd, char **envp)
{
	if (cmd && cmdargs && envp && (cmd[0] == '.' || cmd[0] == '/'))
		execve(cmd, cmdargs, envp);
	if (access(path, F_OK) == 0)
	{
		if (execve(path, cmdargs, envp) == -1)
			wrong_cmd(path);
	}
	wrong_cmd(cmd);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	unsigned char *str1;
	unsigned char *str2;

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

char	*getPath(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	dir = NULL;
	while (env[i] && strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (cmd && cmd[0] != '\0' && cmd[0] != '.' && cmd[0] != '/' && path && ft_int_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_int_strchr(path, ':'));
		bin = ft_strjoine(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		if (ft_int_strchr(path, ':') != ft_strlen(path))
			path += ft_int_strchr(path, ':') + 1;
		else
			break;
	}
	if (dir && (ft_int_strchr(path, ':') == ft_strlen(path) || !path[0]))
		wrong_cmd(cmd);
	return (cmd);
}

void normal_cmd(t_parse *cmd, char **env)
{
	char *path;

	path = getPath(cmd->cmd, env);
	execute(path, cmd->argv, cmd->cmd, env);
}

void execution(t_parse *cmd)
{
	if (cmd->cmd && builtins_cases(cmd))
	{
		execute_builtins(cmd, &g_shell.ev);
	}
	else if (cmd->cmd)
		normal_cmd(cmd, env_to_tab(&g_shell.ev));
}

void minishell(t_parse *cmd)
{
	int fd[2];
	int fds[2];
	fds[1] = dup(1);
	fds[0] = dup(0);
	ft_here_doc(cmd); // check it later with a command that doesn't exist + output redirection
	if (g_shell.err != 0)
		return;
	if (cmd && cmd->cmd && builtins_cases(cmd) && (cmd->next && !cmd->next->cmd))
	{
		open_redir(cmd, fds, fd);
		if (!g_shell.err)
			execute_builtins(cmd, &g_shell.ev);
		dup2(fds[1], 1);
		dup2(fds[0], 0);
		return;
	}
	while (cmd)
	{
		if (cmd->cmd || cmd->redir)
		{
			pipe(fd);
			if (cmd->cmd && strcmp(cmd->cmd, "./minishell") == 0)
			{
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
			}
			g_shell.pid = fork();
			if (g_shell.pid == 0)
			{
				close(fd[0]);
				open_redir(cmd, fds, fd);
				execution(cmd);
				exit(g_shell.ret);
			}
			else
			{
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
			}
		}
		cmd = cmd->next;
	}
	int i;
	i = 0;
	waitpid(g_shell.pid, &i, 0);
	while(wait(NULL) > 0)
		;
	if (WIFEXITED(i))
		g_shell.ret = WEXITSTATUS(i);
	dup2(fds[1], 1);
	dup2(fds[0], 0);
}