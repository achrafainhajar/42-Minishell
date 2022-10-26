#include"../minishell.h"
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
char	*ft_strndup(char *s1, size_t n)
{
	char *s2;

	if (!(s2 = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	else
		return (ft_strncpy(s2, s1, n));
}
void ft_print_export(t_env *env)
{
    while(env)
    {
        ft_putstr_fd("declare -x ",1);
        ft_putstr_fd(env->key, 1);
        if(env->sep)
        {
            ft_putchar_fd(env->sep, 1);
            ft_putstr_fd("\"", 1);
        }
        if(env->val)
            ft_putstr_fd(env->val, 1);
        if(env->sep)
            ft_putstr_fd("\"", 1);
        ft_putchar_fd('\n', 1);
        env = env->next;
    }
}


char *get_range(char *str,char c)
{
    char *s;
    int i;
    i = 0;
    while(str[i] != c && str[i])
        i++;
    s = malloc(sizeof(char) * i + 1);
    i = 0;
    while(str[i] != c && str[i])
    {
        s[i] = str[i];
        i++;
    }
    s[i] = '\0';
    return(s);

}

void fill_export(char *str,t_env **env)
{
    t_env *new;
    char *s;
    new = malloc(sizeof(t_env));
    s = get_range(str,'=');
            new->sep = 0;
            new->val = NULL;
        new->key = ft_strdup(s);
        if(strchr(str,'='))
        {
            new->sep = '=';
            if(strchr(str,'=') + 1)
                new->val = ft_strdup(strchr(str,'=') + 1);
        }
        lst_add_backenv(env,new);
}

int ft_exist(char *str,t_env *env)
{
    char *s;

    s = get_range(str,'=');
    while(env)
    {
        if(ft_strcmp(s,env->key) == 0)
            return(0);
        env=env->next;
    }
    return(1);
}
void value_modif(char *s,t_env **env)
{
    char *str;
    str = get_range(s,'=');
    t_env *head;
    head = (*env);
    while((*env))
    {
        if(ft_strcmp(str,(*env)->key) == 0)
            break;
        (*env)=(*env)->next;
    }
    if((*env)->sep == 0)
        (*env)->sep = '=';
    (*env)->val =  ft_strdup(1 + strchr(s,'='));
    (*env) = head;
}
void modif_export(t_parse *cmd,t_env **env)
{
    int j = 0;
    g_vars.exit_status = 0;
    while(cmd->argv[j])
    {
        if(ft_check(cmd->argv[j]))
        {
            if(ft_exist(cmd->argv[j],*env))
                fill_export(cmd->argv[j],env);
            else
                value_modif(cmd->argv[j],env);
        }
        j++;
    }
}
void ft_export(t_parse *cmd,t_env **env)
{
    if(cmd->argv[0] == 0)
        ft_print_export(*env);
    else
        modif_export(cmd,env);
}