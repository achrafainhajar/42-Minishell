/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:35:29 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/07 16:38:38 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_token *token)
{
	if (token->next && (token->next->e_type == END
			|| token->next->e_type == PIPE))
	{
		if (token->next->e_type == END)
			errors(3);
		else if (token->next->e_type == PIPE)
			errors(258);
		return (1);
	}
	return (0);
}

void	split_expansion(char *value, t_parse *command)
{
	int		i;
	char	**split;

	i = 0;
	split = NULL;
	split = ft_split2(value);
	if (!command->cmd)
		command->cmd = split[i++];
	while (split && split[i])
		command->argv = (char **)realloc_array(command->argv, split[i++]);
}

int	count_env(t_env **env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_to_tab(t_env **env)
{
	int		i;
	int		len;
	char	**tab;
	t_env	*tmp;

	i = 0;
	len = count_env(env);
	tmp = (*env);
	tab = (char **)f_malloc(sizeof(char *) * (len + 1));
	while (tmp)
	{
		tab[i] = join_3_str(tmp->key, "=", tmp->val);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
