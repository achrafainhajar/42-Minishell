/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aainhaja <aainhaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:02:00 by aainhaja          #+#    #+#             */
/*   Updated: 2022/11/09 23:02:00 by aainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (i <= n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strndup(char *s1, size_t n)
{
	char	*s2;

	s2 = (char *)f_malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (NULL);
	else
		return (ft_strncpy(s2, s1, n));
}

void	ft_print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->sep)
		{
			ft_putchar_fd(env->sep, 1);
			ft_putstr_fd("\"", 1);
		}
		if (env->val)
			ft_putstr_fd(env->val, 1);
		if (env->sep)
			ft_putstr_fd("\"", 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

char	*get_range(char *str,	char c)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	s = f_malloc(sizeof(char) * i + 1);
	i = -1;
	if (c != '+')
	{
		while (str[++i] != c && str[i])
			s[i] = str[i];
	}
	else
	{
		while ((str[++i] != c || str[i + 1] != '=') && str[i])
			s[i] = str[i];
	}
	s[i] = '\0';
	return (s);
}
