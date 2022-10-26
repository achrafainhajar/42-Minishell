#include"../minishell.h"
void new_paths(t_env **env)
{
    t_env *head;
    head = (*env);
    char *tmp;
    while(head)
    {
        if(strcmp(head->key,"PWD") == 0)
        {
            tmp = head->val;
            head->val = ft_strdup(getcwd(NULL,0));
            break;
        }
        head = head->next;
    }
     head = (*env);
    while(head)
    {
        if(strcmp(head->key,"OLDPWD") == 0)
        {
            head->val = tmp;
            break;
        }
        head = head->next;
    }
}
void ft_home(t_env **env)
{
    char *home;

    home = my_getenv((*env), "HOME");
    if(!home)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
		g_vars.exit_status = 1;
    }
    else if(!chdir(home))
    {
        new_paths(env);
    }
    else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		g_vars.exit_status = 1;
	}
    new_paths(env);
}
void ft_minus(t_env **env)
{
    if(!chdir(my_getenv(g_vars.my_env, "OLDPWD")))
    {
        new_paths(env);
    }
}
void ft_cd(t_parse *cmd,t_env **env)
{
    if(!cmd->argv[0] || cmd->argv[0][0] == '\0' || 
        !strcmp(cmd->argv[0],"~"))
        ft_home(env);
    else if(!chdir(cmd->argv[0]))
        new_paths(env);
    else if (!strcmp(cmd->argv[0], "-"))
		ft_minus(env);
    else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(" No such file or directory", 2);
		ft_putchar_fd('\n', 2);
		g_vars.exit_status = 1;
	}
}