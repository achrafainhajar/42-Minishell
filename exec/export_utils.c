/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:27:30 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/10 01:27:42 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	fill_export(char *key, char *val, t_env **env, int flag)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->sep = 0;
	new->val = NULL;
	new->key = ft_strdup(key);
	if (flag)
	{
		new->sep = '=';
		if (val)
			new->val = ft_strdup(val);
		else
			new->val = ft_strdup("");
	}
	lst_add_backenv(env, new);
}

char	*ft_exist(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->key) == 0)
			return (env->key);
		env = env->next;
	}
	return (NULL);
}

void	value_modif(char *key, char *val, t_env **env, int not_plus)
{
	t_env	*head;

	head = (*env);
	while ((*env))
	{
		if (ft_strcmp(key, (*env)->key) == 0)
			break ;
		(*env) = (*env)->next;
	}
	if ((*env)->sep == 0)
		(*env)->sep = '=';
	if (not_plus && val)
		(*env)->val = ft_strdup(val);
	else if (val)
		(*env)->val = ft_strjoin((*env)->val, val, 0);
	else
		(*env)->val = ft_strdup("");
	(*env) = head;
}

int	ft_check_export(char	*str)
{
	if (str[0] <= '9' && str[0] >= '0')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": first numeric char not allowed\n", 2);
		g_shell.ret = 1;
		return (0);
	}
	else if (!str_is_alnum(str) && str[0] != '_')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Special char not allowed\n", 2);
		g_shell.ret = 1;
		return (0);
	}
	return (1);
}
