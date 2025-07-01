/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in_et_out.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:45:00 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 23:41:57 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

int	redirect_output_to_file(t_cmd *cmds, int is_builtin,int *exit_status)
{
	int		fd;
	char	*file;

	file = cmds->redirection->file;
	if (!file || !file[0]|| (cmds->redirection->quote_type == NO_QUOTE && has_space(file)))
		return (handle_ambigous_redirect(is_builtin, exit_status));
	fd = open(file, set_output_flags(cmds), 0644);
	if (fd < 0)
		return (handle_open_errors(cmds, is_builtin, exit_status));
	dup2(fd, STDOUT_FILENO);
	close (fd);
	return (0);
}

int	redirect_input_to_file(t_cmd *cmds, int is_builtin,int *exit_status)
{
	int		fd;
	char	*file;

	file = cmds->redirection->file;
	if (!file || !file[0]
		|| (cmds->redirection->quote_type == NO_QUOTE && has_space(file)))
		return (handle_ambigous_redirect(is_builtin,exit_status));
	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (handle_open_errors(cmds, is_builtin,exit_status));
	dup2(fd, STDIN_FILENO);
	close (fd);
	return (0);
}

void	redirect_input_to_pipe(int read_pipe_end)
{
	dup2(read_pipe_end, STDIN_FILENO);
	close (read_pipe_end);
}

void	redirect_output_to_pipe(int write_pipe_end)
{
	dup2(write_pipe_end, STDOUT_FILENO);
	close (write_pipe_end);
}

void	redirect_input_to_file_here_doc(char *heredoc_file)
{
	int	fd;

	fd = open (heredoc_file, O_RDONLY);
	if (fd < 0)
		return ;
	if (unlink(heredoc_file) == -1)
	{
		perror("error occured while removing here_doc file: ");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
