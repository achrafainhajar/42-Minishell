#include "../minishell.h"
int ft_isalphanum(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        if((str[i] >= 'a' && str[i] <= 'z')
            || (str[i] >= 'A' && str[i] <= 'Z')
            || (str[i] >= '0' && str[i] <= '9'))
            i++;
        else
            return(1);
    }
    return(0);
}
int ft_check(char *str)
{
    if(str[0] <= '9' && str[0] >= '0')
    {
        ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": first numeric char not allowed\n", 2);
        g_vars.exit_status = 1;
		return (0);
    }
    else if(ft_isalphanum(str))
    {
        ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Special char not allowed\n", 2);
        g_vars.exit_status = 1;
        return(0);
    }
    return(1);
}
void ft_unset_utils(char *str,t_env **env)
{
    t_env *head;
    head = (*env);
    t_env *tmp;
    while(head)
    {
        if(strcmp(head->key,str) == 0)
        {
            tmp->next = head->next;
            free(head);
            break;
        }
        tmp = head;
        head = head->next;
    }
}
void ft_unset(t_parse *cmd,t_env **env)
{
    int i;

    i = 0;
    g_vars.exit_status = 0;
    while(cmd->argv[i])
    {
        if(ft_check(cmd->argv[i]))
            ft_unset_utils(cmd->argv[i],env);
        i++;
    }
}