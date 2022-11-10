/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 01:25:21 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/10 01:36:40 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	export_else(t_parse *cmd, t_env	**env, char	*tmp, int j)
{
	tmp = get_range(cmd->argv[j], '+');
	if (ft_exist(tmp,*env))
	{
		if (ft_check(tmp, 1))
			value_modif(tmp, strchr(cmd->argv[j], '=') + 1,
				env, 0);
	}
	else if (ft_check(tmp, 1))
		fill_export(tmp, strchr(cmd->argv[j], '=') + 1, env, 1);
	free(tmp);
}

void	export_if(t_parse *cmd, t_env	**env, char	*tmp, int j)
{
	tmp = get_range(cmd->argv[j], '=');
	if (ft_exist(tmp,*env))
	{
		if (ft_check(ft_split(cmd->argv[j], '=')[0], 1))
			value_modif(ft_split(cmd->argv[j], '=')[0],
				strchr(cmd->argv[j], '=') + 1, env, 1);
	}
	else if (ft_check(ft_split(cmd->argv[j], '=')[0], 1))
		fill_export(ft_split(cmd->argv[j], '=')[0],
			strchr(cmd->argv[j], '=') + 1, env, 1);
	free(tmp);
}

void	modif_export(t_parse *cmd, t_env **env)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	if (strcmp(cmd->argv[0], "--") == 0)
		j++;
	while (cmd->argv[j])
	{
		if (cmd->argv[j][0] != '=' && cmd->argv[j][0] != '+')
		{
			if (strchr(cmd->argv[j], '='))
			{
				if (*(strchr(cmd->argv[j], '=') - 1) != '+')
					export_if(cmd, env, tmp, j);
				else
					export_else(cmd, env, tmp, j);
			}
			else if (ft_check(cmd->argv[j], 1) && !ft_exist(cmd->argv[j], *env))
				fill_export(cmd->argv[j], NULL, env, 0);
		}
		else
			ft_check(cmd->argv[j], 1);
		j++;
	}
}

void	ft_export(t_parse *cmd,	t_env	**env)
{
	if (cmd->argv[0] == 0 || (!strcmp(cmd->argv[0], "--") && !cmd->argv[1]))
		ft_print_export(*env);
	else
	{
		g_shell.ret = 0;
		modif_export(cmd, env);
	}
}
