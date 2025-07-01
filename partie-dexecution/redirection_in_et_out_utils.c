/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in_et_out_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:51 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 15:43:55 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_for_redirections(t_commands *cmds, int is_builtin)
{
	while (cmds && cmds->redirections)
	{
		if (cmds->redirections->type == TOKEN_REDIRECT_IN)
		{
			if (redirect_input_to_file(cmds, is_builtin, &g_exit_status) < 0)
				return (-1);
		}
		if (cmds->redirections->type == TOKEN_REDIRECT_OUT || cmds->redirections->type == TOKEN_APPEND)
		{
			if (redirect_output_to_file(cmds, is_builtin,&g_exit_status) < 0)
				return (-1);
		}
		if (cmds->redirections->type == TOKEN_HEREDOC)
		{
			redirect_input_to_file_here_doc(cmds->here_doc_file);
		}
		cmds->redirections = cmds->redirections->next;
	}
	return (0);
}

bool has_space(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] <= ' ')
			return (true);
		i++;
	}
	return (false);
}

int set_output_flags(t_commands *cmd)
{
	if (cmd->redirections->type == TOKEN_REDIRECT_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else
		return (O_WRONLY | O_CREAT | O_APPEND);
}

int handle_ambigous_redirect(int is_builtin, int *exit_status)
{
	if (is_builtin)
	{
		*exit_status = custom_error(ERR_AMBIG_REDIRECT, "$...",
									EXIT_FAILURE, is_builtin);
		return (-1);
	}
	else
		custom_error(ERR_AMBIG_REDIRECT, "$...", EXIT_FAILURE, is_builtin);
	return (0);
}

int handle_open_errors(t_commands *cmds, int is_builtin,int *exit_status)
{
	if (is_builtin)
	{
		*exit_status = custom_error(ERR_PERMISSION, cmds->redirections->file,
									EXIT_FAILURE, is_builtin);
		return (-1);
	}
	else
		custom_error(ERR_PERMISSION, cmds->redirections->file,
					 EXIT_FAILURE, is_builtin);
	return (0);
}
