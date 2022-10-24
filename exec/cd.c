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
void ft_cd(t_parse *cmd,t_env **env)
{
    t_env *head;
    head = (*env);
    if(!cmd->argv[0])
    {
        while(head)
        {
            if(!strcmp(head->key,"HOME"))
            {
                chdir(head->val);
                break;
            }
            head=head->next;
        }
        new_paths(env);
    }
    else if(!chdir(cmd->argv[0]))
        new_paths(env);
}