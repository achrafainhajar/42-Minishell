#include "../minishell.h"
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
    while(cmd->argv[i])
    {
        ft_unset_utils(cmd->argv[i],env);
        i++;
    }
}