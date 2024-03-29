/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 22:34:27 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:50:36 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_squote(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	int		size;
	char	*val;

	size = 0;
	if (g_shell.err == 1)
	{
		advance_lexer(lexer);
		return ;
	}
	advance_lexer(lexer);
	if (ft_int_strchr(&(lexer->str[lexer->i]), '\'') >= 0 && ft_int_strchr
		(&(lexer->str[lexer->i]), '\'') != ft_strlen(&(lexer->str[lexer->i])))
		size = ft_int_strchr(&(lexer->str[lexer->i]), '\'');
	else
		errors(2);
	val = ft_strsub(lexer, size);
	if (g_shell.err == 1)
		return ;
	advance_lexer(lexer);
	token = init_token(val, SQUOTE);
	if (lexer->c != '|' && lexer->c != '>' && lexer->c != '<'
		&& ft_is_space(lexer->c) && lexer->c != '\0')
		token->flag = 1;
	*tmp = lst_add_back(*tmp, token);
}

void	tokenize_dquote(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	int		size;
	char	*val;

	size = 0;
	if (g_shell.err == 1)
	{
		advance_lexer(lexer);
		return ;
	}
	advance_lexer(lexer);
	if (ft_int_strchr(&(lexer->str[lexer->i]), 34) >= 0 && ft_int_strchr
		(&(lexer->str[lexer->i]), '"') != ft_strlen(&(lexer->str[lexer->i])))
		size = ft_int_strchr(&(lexer->str[lexer->i]), 34);
	else
		errors(2);
	val = ft_strsub(lexer, size);
	if (g_shell.err == 1)
		return ;
	advance_lexer(lexer);
	token = init_token(val, DQUOTE);
	if (lexer->c != '>' && lexer->c != '<' && lexer->c != '|'
		&& ft_is_space(lexer->c) && lexer->c != '\0')
		token->flag = 1;
	*tmp = lst_add_back(*tmp, token);
}

void	tokenize_dollar(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	char	*val;

	token = NULL;
	val = if_only_dollar(lexer);
	if (lexer->c == '0' || !ft_isdigit(lexer->c))
	{
		if (lexer->c == '$')
			val = ft_strjoin(val, ft_strsub(lexer, 1), f_malloc);
		else if (lexer->c == '?')
			val = ft_strjoin(val, ft_strsub(lexer, 1), f_malloc);
		else if (ft_is_ex_token(lexer->c))
			val = ft_strjoin(val, " ", f_malloc);
		token = init_token(val, DOLLAR);
		if (lexer->c != '>' && lexer->c != '<' && lexer->c != '|'
			&& ft_is_space(val[1]) && ft_is_space(lexer->c) && lexer->c != '\0')
			token->flag = 1;
		*tmp = lst_add_back(*tmp, token);
	}
	else
		advance_lexer(lexer);
}

void	tokenize_word(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	int		size;
	char	*val;

	size = 0;
	token = NULL;
	if (token_index(&(lexer->str[lexer->i])))
		size = token_index(&(lexer->str[lexer->i]));
	else
		size = ft_int_strchr(&(lexer->str[lexer->i]), '\0');
	val = ft_strsub(lexer, size);
	token = init_token(val, WORD);
	if (lexer->c != '>' && lexer->c != '<' && lexer->c != '|'
		&& ft_is_space(lexer->c) && lexer->c != '\0')
		token->flag = 1;
	*tmp = lst_add_back(*tmp, token);
}

void	tokenize_out_redir(t_token **tmp, t_lexer *lexer)
{
	t_token	*token;
	int		type;
	char	*val;

	token = NULL;
	if (lexer->str[lexer->i + 1] == '>')
	{
		type = GREATANDGREAT;
		val = ft_strsub(lexer, 2);
		token = init_token(val, type);
		*tmp = lst_add_back(*tmp, token);
	}
	else
	{
		type = GREAT;
		val = ft_strsub(lexer, 1);
		token = init_token(val, type);
		*tmp = lst_add_back(*tmp, token);
	}
}
