/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:30 by hlachkar          #+#    #+#             */
/*   Updated: 2022/11/15 22:59:05 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer
{
	char	*str;
	char	c;
	int		i;
}			t_lexer;

typedef struct s_token
{
	char			*val;
	int				flag;
	struct s_token	*next;
	enum
	{
		WORD,
		DQUOTE,
		SQUOTE,
		PIPE,
		GREATANDGREAT,
		LESSANDLESS,
		GREAT,
		LESS,
		DOLLAR,
		END,
	} e_type;
}		t_token;

typedef struct s_redir
{
	char			*file;
	int				e_type;
	int				error;
	int				fdout;
	int				fdin;
	struct s_redir	*next;

}		t_redir;

typedef struct s_parse
{
	char			*cmd;
	char			**argv;
	t_redir			*redir;
	int				error;
	struct s_parse	*next;
}		t_parse;

typedef struct s_env
{
	char			*key;
	char			*val;
	char			sep;
	struct s_env	*next;
}		t_env;

typedef struct s_shell
{
	void	*address[2621444];
	int		i;
	int		ret;
	pid_t	pid;
	int		here_sig;
	int		err;
	int		mik;
	char	*line;
	t_env	*ev;
}		t_shell;

t_shell	g_shell;

void	exit_shell(void);
int		ft_is_space3(char c, int k);
int		skip_aword(char const *s, int *i, int *k);
int		check_expantion(t_token *token);
char	*normal_or_qu(t_token **b, int exec, char *str);
void	normal_cmd(t_parse	*cmd, char	**env);
int		ft_isalphanum(char *str);
void	ft_errors(char *str, int i);
char	*get_range(char *str,	char c);
void	execute(char *path, char **cmdargs, char *cmd, char **envp);
char	*getpath(char	*cmd, char	**env);
char	*ft_exist(char *str, t_env *env);
void	fill_export(char *key, char *val, t_env **env, int flag);
void	value_modif(char *key, char *val, t_env **env, int not_plus);
void	ft_print_export(t_env *env);
char	**ft_split2(char const *s);
int		ft_is_space(char c);
int		syntax_error(t_token *token);
void	split_expansion(char *value, t_parse *command);
void	ctrls(int sig);
t_lexer	*ft_init_lexer(char *str, char c);
void	minishell(t_parse *cmd);
char	**env_to_tab(t_env **env);
t_lexer	*advance_lexer(t_lexer *lexer);
t_token	*send_lexer_to_tokenize(t_lexer *lexer);
t_token	*init_token(char *val, int type);
t_token	*lst_add_back(t_token *lst, t_token *new);
t_parse	*init_command(void);
t_parse	*add_command(t_parse *commad);
t_redir	*add_redir(t_redir *redir, char *val, int type, int error);
t_redir	*init_redir(char *val, int type, int error);
void	dup_files(int exe, int fin, int fout);
void	tokenize_pipe(t_token **tmp, t_lexer *lexer);
void	tokenize_in_redir(t_token **tmp, t_lexer *lexer);
void	tokenize_squote(t_token **tmp, t_lexer *lexer);
void	tokenize_word(t_token **tmp, t_lexer *lexer);
void	tokenize_dollar(t_token **tmp, t_lexer *lexer);
void	tokenize_dquote(t_token **tmp, t_lexer *lexer);
void	tokenize_out_redir(t_token **tmp, t_lexer *lexer);
void	tokenize_end(t_token **tmp);
t_env	*lst_new(char *key, char sep, char *val);
char	*ft_strsub(t_lexer *lexer, size_t len);
int		ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
int		ft_isalpha(int c);
int		str_digit(char *str);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
void	*f_malloc(size_t size);
char	*ft_strjoin(char *s1, char *s2, void *alloc(size_t size));
char	*jme3arg(t_token **b, int exec, int ch_d, int exp);
char	*join_3_str(char *s1, char *s2, char *s3);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
int		ft_int_strchr(const char *s, int c);
int		token_index(char *str);
void	*realloc_array(char **arg, char *str);
void	create_commands(t_token *token, t_parse **command);
char	*expand_dollar(char *dq_content, int exec);
void	execute_builtins(t_parse *cmd, t_env **env);
char	**ft_split(char const *s, char c);
void	ft_pwd(void);
void	free_2(char **tmp);
void	ft_env(t_env *env, t_parse *cmd);
void	errors(int exitt);
int		str_sp_chr(char *str);
char	*check_sp_chr(t_token *b);
char	*dollar_q_d(t_token **b);
char	*dollar_qu(t_token **b, int exec, char *str);
char	*normal_expansion(t_token **b, int f);
void	checkin_dollar(t_token **b, char **str, int ch_d);
void	init_env(char **env);
int		ft_is_ex_token(char c);
char	*ft_strcpy(char *dest, char *src);
char	*my_getenv(t_env *env, char *key);
char	*my_getenv_key(t_env **env, char *key);
int		builtins_cases(t_parse *cmd);
void	lst_add_backenv(t_env **lst, t_env *new);
void	ft_export(t_parse *cmd, t_env **t_env);
void	ft_exit(t_parse *cmd);
void	ft_echo(t_parse *cmd);
char	*if_only_dollar(t_lexer *lexer);
void	ft_unset(t_parse *cmd);
t_parse	*lst_add_back_command(t_parse *lst, t_parse *new);
void	wrong_cmd(char *cmd);
void	c_signal(void);
void	open_redir(t_parse *cmd, int *fds, int *fd);
int		only_enter(void);
char	*ft_strndup(char *s1, size_t n);
int		ft_is_space2(void);
void	ft_cd(t_parse *cmd, t_env **env);
int		ft_check(char *str, int a);
void	ft_here_doc(t_parse *cmd);
char	**ft_split_env(char const *s, char c);
char	*ft_strdup_env(char *s1);
void	update_pwd(t_env **env, t_env *head, char *tmp);

#endif
