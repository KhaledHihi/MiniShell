/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:10:17 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/02 16:09:58 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit;

static int	run_here_doc(t_cmd *cmd_list, t_env *env_list)
{
	if (heredoc(cmd_list, env_list) == -1)
	{
		print_error("Error: heredoc failed\n");
		return (0);
	}
	if (cmd_list->signal_detected)
		return (0);
	return (1);
}

int	check_unvalide_cmds_error(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->token_type == PIPE && tmp->next == NULL)
			return (0);
		if (tmp->token_type == PIPE)
		{
			tmp = tmp->next;
			if (tmp->token_type == PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 32)
			return (0);
		i++;
	}
	return (1);
}
static void	parsing_cmd(char *input, t_exec_env *exec_env)
{
	t_token		*tokens;
	t_env		*env_list;
	t_cmd		*cmd_list;

	tokens = tokenize(input);
	if (!tokens)
	{
		g_exit = 2;
		print_error("minishell: syntax error\n");
		return ;
	}
	// print_node(tokens);
	env_list = init_env(exec_env->env);
	expand_variables_and_remove_quotes(tokens, env_list);
	cmd_list = prs_cmd(tokens);
	// print_cmd(cmd_list);
	if (!cmd_list || !check_cmds(tokens))
	{
		g_exit = 2;
		print_error("minishell: syntax error\n");
		return ;
	}
	if (!run_here_doc(cmd_list, env_list))
		return ;
	launch_execution(cmd_list, exec_env);
}

static void	read_line_process(t_exec_env *env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			ft_malloc(0, 1);
			break ;
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		if (only_spaces(input))
		{
			free(input);
			continue ;
		}
		parsing_cmd(input, env);
		 free(input);
	}
}

static char	**create_new_env(void)
{
	char	**new_env;
	char	*tmp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	new_env = ft_malloc(sizeof(char *) * 5, 0);
	if (!new_env)
		return (NULL);
	tmp = ft_strjoin("PWD=", cwd);
	new_env[0] = ft_strdup(tmp);
	new_env[1] = ft_strdup("SHLVL=1");
	new_env[2] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	new_env[3] = ft_strdup("_=./minishell");
	new_env[4] = NULL;
	free(cwd);
	return (new_env);
}

int	main(int ac, char *av[], char **env)
{
	t_exec_env	envir;

	(void)av;
	if (!env || !env[0])
	{
		envir.env = create_new_env();
		envir.is_created = 1;
	}
	else
	{
		envir.env = copy_env(env);
		envir.is_created = 0;
	}
	if (ac != 1)
		custom_error("Error: run only the programme", "", 1, 0);
	update_shell_level(&envir);
	handle_parent_signals();
	read_line_process(&envir);
	ft_malloc(0, 1);
	clear_history();
	return (0);
}
