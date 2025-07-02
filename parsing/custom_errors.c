/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:55:05 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/02 12:56:03 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	custom_error(char *err_msg, char *arg, int exit_code, int is_builtin)
{
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	if (!is_builtin)
	{
		ft_malloc(0, 1);
		ft_exit(exit_code);
	}
	return (exit_code);
}
void	manage_shell_errors(char *arg, char *path)
{
	if (!arg)
	{
		ft_malloc(0, 0);
		ft_exit(EXIT_FAILURE);
	}
	if (!path)
		custom_error(ERR_CMD_NOT_FOUND, arg, 127, false);
	if (ft_strncmp(path, "no file", ft_strlen(path)) == 0)
		custom_error(ERR_NO_FILE, arg, 127, false);
}

int	handle_fork_errors(int pid)
{
	if (pid == -1)
	{
		perror("an error occured while forking processes: ");
		g_exit = EXIT_FAILURE;
		return (-1);
	}
	return (1);
}

int	check_cmds(t_token *tokens)
{
	t_token	*tmp_tokens;

	tmp_tokens = tokens;
	while (tmp_tokens)
	{
		if (tmp_tokens->token_type == PIPE && tmp_tokens->next == NULL)
			return (0);
		if (tmp_tokens->token_type == PIPE)
		{
			tmp_tokens = tmp_tokens->next;
			if (tmp_tokens->token_type == PIPE)
				return (0);
		}
		tmp_tokens = tmp_tokens->next;
	}
	return (1);
}
