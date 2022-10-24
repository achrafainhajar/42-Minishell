#include"../minishell.h"
int	builtins_cases(t_parse *cmd)
{
	if (!ft_strcmp(cmd->cmd, "echo")|| !ft_strcmp(cmd->cmd, "cd")
		|| !ft_strcmp(cmd->cmd, "pwd") || !ft_strcmp(cmd->cmd, "export")
		|| !ft_strcmp(cmd->cmd, "unset") || !ft_strcmp(cmd->cmd, "env")
		|| !ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}
void execute_builtins(t_parse *cmd,t_env **env)
{
    cmd->argv++;
    if (!strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
    else if (!strcmp(cmd->cmd, "pwd"))
		ft_pwd();
	else if (!strcmp(cmd->cmd, "env"))
		ft_env((*env));
	else if (!strcmp(cmd->cmd, "export"))
		ft_export(cmd,env);
	else if (!strcmp(cmd->cmd, "unset"))
		ft_unset(cmd,env);
	else if (!strcmp(cmd->cmd, "cd"))
		ft_cd(cmd,env);
	cmd->argv--;
}