/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:10:41 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/19 15:31:44 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
#define MINI_SHELL_H

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
# include "libft/libft.h"

typedef enum s_type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	SEMICOLON,
}					t_type;

typedef enum s_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}					t_quote_type;


typedef struct s_token
{
	char			*value;
	t_type			token_type;
	t_quote_type	quote_type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;


typedef struct s_redirection
{
	char *file;
	t_type	type;
	t_quote_type	quote_type;
	struct s_redirection *next;
}					t_redirection;

typedef struct s_cmd
{
	char 			**arg;
	char 			**env;
	int				append;
	int				heredoc;
	char			*heredoc_file;
	t_redirection	*redirection;
	struct s_cmd 	*next;
}					t_cmd;

t_token *tokenize(char *input);
void 	print_node(t_token *list);
t_env   *int_env(char **env);
void 	print_lst(t_env *list);
t_cmd	*prs_cmd(t_token *tokens);
char **realoc_arr(char **arr, char *str);
void print_cmd(t_cmd *cmd);
void	*ft_malloc(size_t size, int type);
void expand_variables_and_remove_quotes(t_token *tokens, t_env *env);
char	*ft_strjoin_char(char const *s1, char s2);

#endif
