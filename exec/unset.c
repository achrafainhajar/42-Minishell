/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:21:32 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 23:21:32 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check(char *str, int flag)
{
	if (str[0] <= '9' && str[0] >= '0' && str[0] != '\0')
	{
		if (flag == 0)
			ft_putstr_fd("unset: ", 2);
		else
			ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": first numeric char not allowed\n", 2);
		g_shell.ret = 1;
		return (0);
	}
	else if (ft_isalphanum(str))
	{
		if (flag == 0)
			ft_putstr_fd("unset: ", 2);
		else
			ft_putstr_fd("export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Special char not allowed\n", 2);
		g_shell.ret = 1;
		return (0);
	}
	return (1);
}

void	ft_unset_utils(char *str, t_env **env)
{
	t_env	*head;
	t_env	*tmp;

	if (strcmp((*env)->key, str) == 0)
	{
		tmp = (*env);
		(*env) = (*env)->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
	else
	{
		head = (*env);
		while (head)
		{
			if (strcmp(head->key, str) == 0)
			{
				tmp->next = head->next;
				free(head->key);
				free(head->val);
				free(head);
				break ;
			}
			tmp = head;
			head = head->next;
		}
	}
}

void	ft_unset(t_parse *cmd)
{
	int	i;

	i = 0;
	g_shell.ret = 0;
	while (cmd->argv[i])
	{
		if (ft_check(cmd->argv[i], 0))
			ft_unset_utils(cmd->argv[i], &g_shell.ev);
		i++;
	}
}
