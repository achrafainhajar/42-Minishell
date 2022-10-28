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
void ft_home(void)
{
    char *home;

    home = my_getenv(g_vars.my_env, "HOME");
    if(!home)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
		g_vars.exit_status = 1;
    }
    else if(!chdir(home))
    {
        new_paths(&g_vars.my_env);
    }
}
void ft_minus(t_env **env)
{
    if(!chdir(my_getenv(g_vars.my_env, "OLDPWD")))
    {
        new_paths(env);
        ft_putstr_fd(my_getenv(*env, "PWD"), 1);
        ft_putchar_fd('\n', 1);
    }
    else
    {
        ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(my_getenv(*env, "OLDPWD"), 2);
        ft_putstr_fd(" No such file or directory", 2);
		ft_putchar_fd('\n', 2);
		g_vars.exit_status = 1;
    }
}
void    cd_tilde(char *path)
{
    char    *dir;
    ft_home();
    if (g_vars.exit_status != 1 && ft_strcmp(path, "~") != 0)
    {
        dir = strchr(path, '/');
        if (dir)
        {
            dir++;
            if (chdir(dir) != 0)
            {
                ft_putstr_fd("minishell: cd: ", 2);
		        ft_putstr_fd(path, 2);
		        ft_putstr_fd(" No such file or directory", 2);
		        ft_putchar_fd('\n', 2);
                g_vars.exit_status = 1;
            }
            else
                new_paths(&g_vars.my_env);
        }
        else
        {
            ft_putstr_fd("minishell: cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(" No such file or directory", 2);
            ft_putchar_fd('\n', 2);
            g_vars.exit_status = 1;
        }
    }
}

void ft_cd(t_parse *cmd,t_env **env)
{
    if (cmd->argv[0] && cmd->argv[1] != NULL)
    {
        ft_putstr_fd("minishell: cd: too many arguments", 2);
		ft_putchar_fd('\n', 2);
		g_vars.exit_status = 1;
    }
    else if(!cmd->argv[0])
        ft_home();
    else if (cmd->argv[0][0] == '~')
        cd_tilde(cmd->argv[0]);
    else if (!strcmp(cmd->argv[0], "-"))
		ft_minus(env);
    else if(!chdir(cmd->argv[0]))
    {
        if (getcwd(NULL, 0))
            new_paths(env);
        else
            ft_putstr_fd("cd: error retrieving current directory\n", 2);
    }
    else if (cmd->argv[0][0] != '\0')
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(" No such file or directory", 2);
		ft_putchar_fd('\n', 2);
		g_vars.exit_status = 1;
	}
}