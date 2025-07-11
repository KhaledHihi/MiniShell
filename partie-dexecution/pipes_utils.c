/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:46 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 18:01:24 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input_redirections(t_redirection *redirections, t_cmd *cmds)
{
	t_redirection	*current;
	int				redirected;

	redirected = 0;
	if (!redirections)
		return (0);
	current = redirections;
	while (current)
	{
		if (current->type == REDIRECT_IN)
		{
			redirect_input_to_file(cmds, 0, &g_exit);
			redirected = 1;
		}
		else if (current->type == HEREDOC)
		{
			if (!cmds->arg && cmds->heredoc)
				return (0);
			redirect_input_to_file_here_doc(cmds->heredoc_file);
			return (1);
		}
		current = current->next;
	}
	return (redirected);
}

void	close_unused_pipes(int (*pipes)[2], int n_of_pipes, int except)
{
	int	i;

	i = 0;
	while (i < n_of_pipes)
	{
		if (i != except)
		{
			close (pipes[i][0]);
			close (pipes[i][1]);
		}
		i++;
	}
}

void	wait_for_childs(t_cmd *cmds, int *pids, int n_of_cmds)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < n_of_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status) && (i == n_of_cmds - 1))
			g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
		if (g_exit == 130 && !cmds->heredoc)
			printf("\n");
		i++;
	}
}

void	allocate_pipes_and_pids(int (**pipes)[2], int **pids, int n_of_cmds)
{
	*pipes = ft_malloc(sizeof(int [2]) * (n_of_cmds - 1), 0);
	*pids = ft_malloc(sizeof(int) * n_of_cmds, 0);
	if (!pids || !pipes)
	{
		perror("Failed to allocate pipes or pids: ");
		return ;
	}
}

void	create_pipes(int (*pipes)[2], int n_of_cmds)
{
	int	i;

	i = 0;
	while (i < n_of_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("an error occured while creating pipes: ");
			g_exit = EXIT_FAILURE;
			return ;
		}
		i++;
	}
}
