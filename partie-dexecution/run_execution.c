/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:26 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 14:34:31 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void ft_close_duplicated_fds(int s_out, int s_in)
{
	close(s_out);
	close(s_in);
}

void builtin_second(t_cmd *cmds, t_exec_env *exec_env)
{
	int saved_stdout;
	int saved_stdin;
	int status;

	status = 0;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	status = check_for_redirections(cmds, true);
	if (status >= 0)
		status = execute_builtin(cmds->arg, exec_env, g_exit);
	if (status == -1)
		status = EXIT_FAILURE;
	g_exit = status;
	if (ft_strncmp(cmds->arg[0], "exit", ft_strlen("exit")) == 0)
	{
		printf("exit\n");
		ft_malloc(0, 1);
		ft_close_duplicated_fds(saved_stdout, saved_stdin);
		ft_exit(g_exit);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	ft_close_duplicated_fds(saved_stdout, saved_stdin);
}

void extern_last(t_cmd *cmds, t_exec_env *exec_env)
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
		execute_command(cmds->arg, exec_env->env);
	}
	signal (SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	handle_parent_signals();
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = 128 + WTERMSIG(status);
	if (g_exit == 130)
		printf("\n");
	if (g_exit == 131)
		printf("Quit (core dumped)\n");
}

int count_n_of_cmds(t_cmd *cmds)
{
	int count;
	t_cmd *tmp;

	count = 0;
	tmp = cmds;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int launch_execution(t_cmd *cmds, t_exec_env *exec_env)
{
	int n_of_cmds;

	n_of_cmds = count_n_of_cmds(cmds);
	if (n_of_cmds > 1)
		pipe_first(cmds, n_of_cmds, exec_env);
	else
	{
		if (cmds->arg && is_builtin(cmds->arg[0]))
			builtin_second(cmds, exec_env);
		else
			extern_last(cmds, exec_env);
	}
	return (0);
}
