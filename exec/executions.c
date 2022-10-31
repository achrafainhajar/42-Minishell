#include "../minishell.h"
void	wrong_cmd(char *cmd)
{
	write(2, "mino: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}
char	*ft_strjoine(char *s1, char  *s2)
{
	int		i;
	char	*str;
	int		b;

	if (!s1 || !s2)
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!str)
		return (NULL);
	i = 0;
	b = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
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

void	execute(char	**path, char		**cmdargs,char *cmd, char	**envp)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		if (cmd[0] != '.')
		{
			tmp = ft_strjoine(path[i], cmd);
		}
		else
		{
			tmp = cmd;
		}
		if (access(tmp, F_OK) == 0)
		{
			execve(tmp, cmdargs, envp);
		}
		i++;
	}
	wrong_cmd(cmdargs[0]);
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

void	normal_cmd(t_parse *cmd,char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp (env[i], "PATH=", 5) == 0)
		{
			break ;
		}
		i++;
	}
	path = ft_split(env[i], ':'); 
	execute(path,cmd->argv,cmd->cmd,env);
}

void execution(t_parse *cmd)
{
	if(builtins_cases(cmd) && g_shell.ret == 0)
	{
		execute_builtins(cmd,&g_shell.ev);
	}
	else if (g_shell.ret == 0)
		normal_cmd(cmd,env_to_tab(&g_shell.ev));
}

void	last_cmd(t_parse *cmd,int fds[2],int fd[2])
{
	if(cmd)
    {
        if(cmd->next && cmd)
        {
        	pipe(fd);
			if (strcmp(cmd->cmd, "./minishell") == 0)
			{
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
			}
			g_shell.pid = fork();
        	if(g_shell.pid == 0)
			{
				close(fd[0]);
				open_redir(cmd,fds,fd);
				execution(cmd);
				exit(g_shell.ret);
			}
			close(fd[1]);
        	cmd = cmd->next;
		}
    }
}

void minishell(t_parse *cmd)
{
    int fd[2];
	int fds[2];
	fds[1] = dup(1);
	fds[0] = dup(0);
	ft_here_doc(cmd);

	if(g_shell.ret == 0 && cmd && cmd->cmd && builtins_cases(cmd) && !cmd->next->cmd)
	{
		open_redir(cmd,fds,fd);
		execute_builtins(cmd,&g_shell.ev);
		dup2(fds[1], 1);
		dup2(fds[0], 0);
		return ;
	}
	while(g_shell.ret == 0 && cmd && cmd->next && cmd->next->next)
	{
		pipe(fd);
		g_shell.pid = fork();
		if(g_shell.pid == 0)
		{
			close(fd[0]);
			open_redir(cmd,fds,fd);
			execution(cmd);
			exit(g_shell.ret);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		cmd = cmd->next;
	}
	if (g_shell.ret == 0)
	{
		last_cmd(cmd,fds,fd);
	}
	
	dup2(fds[1], 1);
	dup2(fds[0], 0);
	int i;
	i = 0;
    while(wait(&i) > 0)
		;
}