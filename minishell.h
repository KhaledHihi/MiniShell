/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:59:39 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/02 13:20:09 by khhihi           ###   ########.fr       */
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
# include <sys/stat.h>
# define ERR_NO_FILE "minishell: no such file or directory: "
# define ERR_PERMISSION "minishell: permission denied: "
# define ERR_CMD_NOT_FOUND "minishell: command not found: "
# define ERR_AMBIG_REDIRECT "minishell: ambiguous redirect: "
// # define PATH_MAX 1024
# define MAX_HEREDOCS 16

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
	int						exit_status;
	int						heredoc;
	char					*heredoc_file;
	t_redirection			*redirection;
	t_quote_type			quote_type;
	int						signal_detected;
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
t_env	*init_env(char **env);
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
int	check_cmds(t_token *tokens);
void	print_error(char *msg);

// Additional parsing functions
char	*limiter(char *limiter);
char	*expand_variable_value(char *word, t_env *env, int *heredoc);
char	*expand_the_heredoc(char *input_heredoc, t_env *env);
char	*get_word_value(char *input, int *i, t_quote_type *quote_type);
char	*get_op(char *input, int *i);
t_type	get_token_type(char *value);
int		handle_next_token(char *input, int *i, t_token **tokens);
void	print_redirection_list(t_redirection *redir);
t_env	*create_env_node(char *env_var);
void	append_env_node(t_env **lst, t_env *new_env);
t_cmd	*create_new_cmd(void);
void	add_cmd_to_lst(t_cmd **lst, t_cmd *new);
void	add_redirections(t_cmd *current_cmd, t_redirection *new_redir);
void	manage_shell_errors(char *arg, char *path);
int		handle_fork_errors(int pid);
int		heredoc(t_cmd *cmds, t_env *env);
int		count_here_doc(t_cmd *cmds, char ***files);
int		count_redirections(t_cmd *cmds);
void	ign_ctrl_c_with_exit_status(int pid, int *status, int *signal_detected);
void	unlink_files(int total_here_doc, char **files);
void	print_error(char *msg);
int		check_cmds(t_token *tokens);

// functions that need to be implemented
char	*expand_env_variable(const char *word, int *i, t_env *env, char *result);
char	*case_of_var_start_with_digit(char *word, int *i, char *res);
char	*case_of_word(char *input_heredoc, int *i, char *result);
char	**realoc_arr(char **arr, char *str);

// execution part

// pipes_utils.c
int		handle_input_redirections(t_redirection *redirections, t_cmd *cmds);
void	close_unused_pipes(int (*pipes)[2], int n_of_pipes, int except);
void	wait_for_childs(t_cmd *cmds, int *pids, int n_of_cmds);
void	allocate_pipes_and_pids(int (**pipes)[2], int **pids, int n_of_cmds);
void	create_pipes(int (*pipes)[2], int n_of_cmds);

// redirection_in_et_out_utils.c
int		check_for_redirections(t_cmd *cmds, int is_builtin);
bool	has_space(char *str);
int		set_output_flags(t_cmd *cmd);
int		handle_ambigous_redirect(int is_builtin, int *exit_status);
int		handle_open_errors(t_cmd *cmds, int is_builtin, int *exit_status);

// redirection_in_et_out.c
int		redirect_output_to_file(t_cmd *cmds, int is_builtin, int *exit_status);
int		redirect_input_to_file(t_cmd *cmds, int is_builtin, int *exit_status);
void	redirect_input_to_pipe(int read_pipe_end);
void	redirect_output_to_pipe(int write_pipe_end);
void	redirect_input_to_file_here_doc(char *heredoc_file);

// run_builtin.c
int		get_env_var_index(char **env, char *var);
bool	search_for_env_var(char **env, char *var);
int		has_equal_sign(char *var);
int		execute_builtin(char **args, t_exec_env *exec_env, int last_cmd_exit_status);

// run_execution.c
void	builtin_second(t_cmd *cmds, t_exec_env *exec_env);
void	extern_last(t_cmd *cmds, t_exec_env *exec_env);
int		count_n_of_cmds(t_cmd *cmds);
int		launch_execution(t_cmd *cmds, t_exec_env *exec_env);

// run_extern_cmds.c
void	execute_command(char **args, char **env);

// execution_pipe.c
void	handle_child_proccesses(t_cmd *cmd, int (*pipes)[2],
		t_exec_pipe *t_pipe, t_exec_env *exec_env);
void	pipe_first(t_cmd *cmds, int n_of_cmds, t_exec_env *exec_env);

// signals.c
void	sig_handler_parent(int sig);
void	sig_handler_child(int signum);
void	handle_parent_signals(void);
void	handle_child_signals(void);

// signales_herdoc.c
void	sig_handler_here_doc(int signum);
void	handle_here_doc_signals(void);

// utils.c
void	ft_exit(int nb);
char	*get_tmp_file(void);
int		is_builtin(char *cmd);
char	**copy_env(char **envp);
void	update_shell_level(t_exec_env *exec_env);

// builtins/builtin_cd.c
int		builtin_cd(char **args, char **env, int is_created);

// builtins/builtin_echo.c
int		builtin_echo(char **args);

// builtins/builtin_env.c
int		builtin_env(char **env);

// builtins/builtin_exit.c
int		builtin_exit(char **args, int last_cmd_exit_status);

// builtins/builtin_export.c
void	handle_plus_sign_feature(t_exec_env *exec_env, char *var);
void	handle_equal_sign_feature(t_exec_env *exec_env, char *var);
int		builtin_export(char **args, t_exec_env *exec_env);

// builtins/builtin_pwd.c
int		builtin_pwd(char **env);

// builtins/builtin_unset.c
int		builtin_unset(char **args, char **env, int is_created);

// builtins/export_utils_1.c
void	add_var_to_env(t_exec_env *exec_env, char *var);
void	append_env_var(t_exec_env *exec_env, char *new_value, int var_index);
void	sort_env(char **env);
void	print_sorted_env(t_exec_env *exec_env);
bool	is_valid_identifier(char *arg);

// builtins/export_utils_2.c
int		ft_get_env_len(char **env);
int		ft_get_env_var_len(char *env_var);
int		ft_max(int value1, int value2);
void	ft_swap(char **s1, char **s2);

#endif
