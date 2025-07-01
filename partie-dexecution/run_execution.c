/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:26 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 16:02:31 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_close_duplicated_fds(int s_out, int s_in)
{
	close(s_out);
	close(s_in);
}

void builtin_second(t_commands *cmds, t_exec_env *exec_env)
{
	int saved_stdout;
	int saved_stdin;
	int status;

	status = 0;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	status = check_for_redirections(cmds, true);
	if (status >= 0)
		status = execute_builtin(cmds->args, exec_env, g_exit_status);
	if (status == -1)
		status = EXIT_FAILURE;
	g_exit_status = status;
	if (ft_strncmp(cmds->args[0], "exit", ft_strlen("exit")) == 0)
	{
		printf("exit\n");
		ft_malloc(0, 0);
		ft_close_duplicated_fds(saved_stdout, saved_stdin);
		ft_exit(g_exit_status);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	ft_close_duplicated_fds(saved_stdout, saved_stdin);
}

void extern_last(t_commands *cmds, t_exec_env *exec_env)
{
	int status;
	int pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork: ");
	if (pid == 0)
	{
		handle_child_signals();
		check_for_redirections(cmds, false);
		execute_command(cmds->args, exec_env->env);
	}
	signal (SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	handle_parent_signals();
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	if (g_exit_status == 130)
		printf("\n");
	if (g_exit_status == 131)
		printf("Quit (core dumped)\n");
}

int count_n_of_cmds(t_commands *cmds)
{
	int count;
	t_commands *tmp;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int launch_execution(t_commands *cmds, t_exec_env *exec_env)
{
	int n_of_cmds;

	n_of_cmds = count_n_of_cmds(cmds);
	if (n_of_cmds > 1)
		pipe_first(cmds, n_of_cmds, exec_env);
	else
	{
		if (cmds->args && is_builtin(cmds->args[0]))
			builtin_second(cmds, exec_env);
		else
			extern_last(cmds, exec_env);
	}
	return (0);
}