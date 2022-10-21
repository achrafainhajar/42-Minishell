#include"../minishell.h"
void ft_env(t_env *env)
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