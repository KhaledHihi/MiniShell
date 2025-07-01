/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:59:39 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/01 22:39:31 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int					g_exit;

typedef enum s_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	SEMICOLON,
}							t_type;

typedef enum s_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}							t_quote_type;

typedef struct s_token
{
	char					*value;
	t_type					token_type;
	t_quote_type			quote_type;
	struct s_token			*next;
}							t_token;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_redirection
{
	char					*file;
	t_type					type;
	t_quote_type			quote_type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmd
{
	char					**arg;
	int						append;
	int						heredoc;
	char					*heredoc_file;
	t_redirection			*redirection;
	t_quote_type			quote_type;
	struct s_cmd			*next;
}							t_cmd;

typedef struct s_exec_env
{
	int						is_created;
	char					**env;
}	t_exec_env;

typedef struct s_exec_pipe
{
	int						index;
	int						n_of_cmds;
	int						is_builtin;
	int						has_return;
	int						*pids;
	int						(*pipes)[2];
}							t_exec_pipe;

typedef struct s_gc
{
	void					*ptr;
	struct s_gc				*next;
}							t_gc;

//parsing part

t_token	*tokenize(char *input);
void	print_node(t_token *list);
t_env	*int_env(char **env);
void	print_lst(t_env *list);
t_cmd	*prs_cmd(t_token *tokens);
char	**realoc_arr(char **arr, char *str);
void	print_cmd(t_cmd *cmd);
void	*ft_malloc(size_t size, int type);
void	expand_variables_and_remove_quotes(t_token *tokens, t_env *env);
char	*ft_strjoin_char(char const *s1, char s2);
char	*case_of_var_with_exit_status(int *i, char *res);
char	*case_of_var_start_with_digit(char *word, int *i, char *res);
char	*handle_single_quotes(const char *word, int *index, char *result);
char	*double_quotes(const char *word, int *index, t_env *env, char *result);
char	*get_env_value(t_env *env, char *key);
char	*case_of_quote_after_var(char *word, int *i, char *res,
			char quote_char);
char	*expand_env_variable(const char *word, int *index, t_env *env,
			char *result);
t_token	*ft_lstnew_token(char *value, t_type type, t_quote_type quote);
void	add_token_back(t_token **head, t_token *new_token);
int		custom_error(char *err_msg, char *arg, int exit_code, int is_builtin);

// execution part

#endif
