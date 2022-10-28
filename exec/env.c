#include"../minishell.h"
void ft_env(t_env *env,t_parse *cmd)
{
    if(!cmd->argv[0])
    {
        while(env)
        {
            if(env->sep)
            {
                ft_putstr_fd(env->key, 1);
                ft_putchar_fd(env->sep, 1);
                ft_putstr_fd(env->val, 1);
                ft_putchar_fd('\n', 1);
            }
            env = env->next;
        }
    }
    else
    {
        ft_putstr_fd("Too many arguments\n",2);
        g_vars.exit_status = 127;
    }
}