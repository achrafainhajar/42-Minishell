#include"../minishell.h"
void ft_pwd()
{
    char *str;

    str = getcwd(NULL,0);
    if(str)
    {
        ft_putstr_fd(str,1);
        ft_putstr_fd("\n",1);
        g_shell.ret = 0;
    }
    else
    {
        ft_putstr_fd("pwd: cannot get working directory\n",2);
        g_shell.ret = 1;    
    }
}