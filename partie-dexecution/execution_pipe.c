/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:39 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 17:59:57 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_output_redirections(t_redirection *redirections,
									t_cmd *cmds)
{
	t_redirection	*current;
	int				redirected;

	redirected = 0;
	if (!redirections)
		return (0);
	current = redirections;
	while (current)
	{
		if (current->type == REDIRECT_OUT)
		{
			cmds->redirection->file = current->file;
			redirect_output_to_file(cmds, 0, &g_exit);
			redirected = 1;
		}
		else if (current->type == APPEND)
		{
			redirect_output_to_file(cmds, 0, &g_exit);
			redirected = 1;
		}
		current = current->next;
	}
	return (redirected);
}

static void	configure_pipeline_io(t_cmd *cmds, int (*pipes)[2],
								t_exec_pipe *t_pipe)
{
	int (redirected_in), (redirected_out);
	if (t_pipe->index == 0)
	{
		redirected_in = handle_input_redirections(cmds->redirection, cmds);
		redirected_out = handle_output_redirections(cmds->redirection, cmds);
		if (!redirected_out)
			redirect_output_to_pipe(pipes[t_pipe->index][1]);
	}
	else if (t_pipe->index == t_pipe->n_of_cmds - 1)
	{
		redirected_in = handle_input_redirections(cmds->redirection, cmds);
		if (!redirected_in)
			redirect_input_to_pipe(pipes[t_pipe->index - 1][0]);
		handle_output_redirections(cmds->redirection, cmds);
	}
	else
	{
		redirected_in = handle_input_redirections(cmds->redirection, cmds);
		if (!redirected_in)
			redirect_input_to_pipe(pipes[t_pipe->index - 1][0]);
		redirected_out = handle_output_redirections(cmds->redirection, cmds);
		if (!redirected_out)
			redirect_output_to_pipe(pipes[t_pipe->index][1]);
	}
}

void	handle_child_proccesses(t_cmd *cmd, int (*pipes)[2],
							t_exec_pipe *t_pipe, t_exec_env *exec_env)
{
	if (cmd->arg && is_builtin(cmd->arg[0]))
	{
		t_pipe->is_builtin = true;
		configure_pipeline_io(cmd, pipes, t_pipe);
		close_unused_pipes(pipes, t_pipe->n_of_cmds - 1, -1);
		g_exit = execute_builtin(cmd->arg, exec_env, 0);
		ft_exit(g_exit);
	}
	else
	{
		t_pipe->is_builtin = false;
		configure_pipeline_io(cmd, pipes, t_pipe);
		close_unused_pipes(pipes, t_pipe->n_of_cmds - 1, -1);
		if (t_pipe->index != t_pipe->n_of_cmds - 1 && cmd->heredoc && cmd->arg)
			ft_exit(0);
		execute_command(cmd->arg, exec_env->env);
	}
}

static void	execute_pipes(t_cmd *cmds, int n_of_cmds,
						t_exec_env *exec_env, t_exec_pipe *t_pipe)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmds;
	i = 0;
	while (tmp && i < n_of_cmds)
	{
		t_pipe->pids[i] = fork();
		if (handle_fork_errors(t_pipe->pids[i]) == -1)
			return ;
		if (t_pipe->pids[i] == 0)
		{
			handle_child_signals();
			t_pipe->index = i;
			handle_child_proccesses(tmp, t_pipe->pipes, t_pipe, exec_env);
		}
		i++;
		tmp = tmp->next;
	}
	signal(SIGINT, SIG_IGN);
	close_unused_pipes(t_pipe->pipes, n_of_cmds - 1, -1);
	wait_for_childs(cmds, t_pipe->pids, n_of_cmds);
	handle_parent_signals();
}

void	pipe_first(t_cmd *cmds, int n_of_cmds, t_exec_env *exec_env)
{
	t_exec_pipe	t_pipe;

	ft_bzero(&t_pipe, sizeof(t_exec_pipe));
	t_pipe.n_of_cmds = n_of_cmds;
	allocate_pipes_and_pids(&t_pipe.pipes, &t_pipe.pids, n_of_cmds);
	create_pipes(t_pipe.pipes, n_of_cmds);
	execute_pipes(cmds, n_of_cmds, exec_env, &t_pipe);
}
