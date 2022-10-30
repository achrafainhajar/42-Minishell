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

int	str_is_alnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
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
    if (c != '+')
    {
        while(str[i] != c && str[i])
        {
            s[i] = str[i];
            i++;
        }
    }
    else
    {
        while((str[i] != c || str[i + 1] != '=') && str[i])
        {
            s[i] = str[i];
            i++;
        }
    }
    s[i] = '\0';
    return(s);

}

void fill_export(char *key, char *val,t_env **env, int flag)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    new->sep = 0;
    new->val = NULL;
    new->key = ft_strdup(key);
    if(flag)
    {
        new->sep = '=';
        if (val)
            new->val = ft_strdup(val);
        else
            new->val = ft_strdup("");
    }
    lst_add_backenv(env,new);
}

char *ft_exist(char *str,t_env *env)
{
    while(env)
    {
        if(ft_strcmp(str,env->key) == 0)
            return(env->key);
        env=env->next;
    }
    return(NULL);
}
void value_modif(char *key, char *val, t_env **env, int not_plus)
{
    // char *str;
    t_env *head;
    
    head = (*env);
    while((*env))
    {
        if(ft_strcmp(key,(*env)->key) == 0)
            break;
        (*env)=(*env)->next;
    }
    if((*env)->sep == 0)
        (*env)->sep = '=';
    if (not_plus && val)
        (*env)->val =  ft_strdup(val);
    else if (val)
        (*env)->val =  ft_strjoin((*env)->val, val, 0);
    else
        (*env)->val = ft_strdup("");
    (*env) = head;
}

int ft_check_export(char *str)
{
    if(str[0] <= '9' && str[0] >= '0')
    {
        ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": first numeric char not allowed\n", 2);
        g_shell.ret = 1;
		return (0);
    }
    else if(!str_is_alnum(str) && str[0] != '_')
    {
        ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Special char not allowed\n", 2);
        g_shell.ret = 1;
        return(0);
    }
    return(1);
}

void modif_export(t_parse *cmd,t_env **env)
{
    int j = 0;

    g_shell.ret = 0;
    if (strcmp(cmd->argv[0], "--") == 0)
        j++;
    while(cmd->argv[j]) ///  a=saas  =csacs _csa=casc _casc=  
    {
        if (cmd->argv[j][0] != '=' && cmd->argv[j][0] != '+')
        {
            if (strchr(cmd->argv[j], '='))
            {
                if (*(strchr(cmd->argv[j], '=') - 1) != '+')
                {
                    if (ft_exist(get_range(cmd->argv[j],'='),*env))
                    {
                        if (ft_check(ft_split(cmd->argv[j], '=')[0], 1))
                            value_modif(ft_split(cmd->argv[j], '=')[0], strchr(cmd->argv[j], '=') + 1, env, 1);
                    }
                    else if (ft_check(ft_split(cmd->argv[j], '=')[0], 1))
                        fill_export(ft_split(cmd->argv[j], '=')[0], strchr(cmd->argv[j], '=') + 1, env, 1);
                }
                else
                {
                    if (ft_exist(get_range(cmd->argv[j],'+'),*env))
                    {
                        if (ft_check(get_range(cmd->argv[j],'+'), 1))
                            value_modif(get_range(cmd->argv[j],'+'), strchr(cmd->argv[j], '=') + 1, env, 0);
                    }
                    else if (ft_check(get_range(cmd->argv[j],'+'), 1))
                        fill_export(get_range(cmd->argv[j],'+'), strchr(cmd->argv[j], '=') + 1, env, 1);
                }
            }
            else if (ft_check(cmd->argv[j], 1) && !ft_exist(cmd->argv[j], *env) )
                fill_export(cmd->argv[j], NULL,env, 0);
        }
        else
            ft_check(cmd->argv[j], 1);
        j++;
    }
}
void ft_export(t_parse *cmd,t_env **env)
{
    if(cmd->argv[0] == 0 || (!strcmp(cmd->argv[0], "--") && !cmd->argv[1]))
        ft_print_export(*env);
    else
        modif_export(cmd,env);
}