/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in_et_out_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:51 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 23:53:03 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_for_redirections(t_cmd *cmds, int is_builtin)
{
	while (cmds && cmds->redirection)
	{
		if (cmds->redirection->type == REDIRECT_IN)
		{
			if (redirect_input_to_file(cmds, is_builtin, &g_exit) < 0)
				return (-1);
		}
		if (cmds->redirection->type == REDIRECT_OUT || cmds->redirection->type == APPEND)
		{
			if (redirect_output_to_file(cmds, is_builtin,&g_exit) < 0)
				return (-1);
		}
		if (cmds->redirection->type == HEREDOC)
		{
			redirect_input_to_file_here_doc(cmds->heredoc_file);
		}
		cmds->redirection = cmds->redirection->next;
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

int set_output_flags(t_cmd *cmd)
{
	if (cmd->redirection->type == REDIRECT_OUT)
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

int handle_open_errors(t_cmd *cmds, int is_builtin,int *exit_status)
{
	if (is_builtin)
	{
		*exit_status = custom_error(ERR_PERMISSION, cmds->redirection->file,
									EXIT_FAILURE, is_builtin);
		return (-1);
	}
	else
		custom_error(ERR_PERMISSION, cmds->redirection->file,
					 EXIT_FAILURE, is_builtin);
	return (0);
}
