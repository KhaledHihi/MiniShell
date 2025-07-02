/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:29:29 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/02 01:30:58 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_the_heredoc(char *input_heredoc, t_env *env)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup("");
	while (input_heredoc[i])
	{
		if (input_heredoc[i] == '$' && input_heredoc[i + 1]
			&& (ft_isalpha(input_heredoc[i + 1]) || input_heredoc[i
					+ 1] == '_'))
			result = case_of_normal_var(input_heredoc, &i, result, env);
		else if (input_heredoc[i] == '$' && input_heredoc[i + 1]
			&& ft_isdigit(input_heredoc[i + 1]))
			result = case_of_var_with_next_char_digit(input_heredoc,
					&i, result);
		else if (input_heredoc[i] == '$' && input_heredoc[i + 1]
			&& input_heredoc[i + 1] == '?')
			result = case_of_var_with_exit_status(&i, result);
		else
			result = case_of_word(input_heredoc, &i, result);
	}
	return (result);
}

int	count_here_doc(t_cmd *cmds, char ***files)
{
	t_cmd		*tmp_cmds;
	t_redirection	*redir;
	int				total;

	tmp_cmds = cmds;
	total = 0;
	while (tmp_cmds)
	{
		redir = tmp_cmds->redirection;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->file)
			{
				*files = ft_realloc_array(*files, get_tmp_file());
				total++;
			}
			redir = redir->next;
		}
		tmp_cmds = tmp_cmds->next;
	}
	return (total);
}

int	count_redirections(t_cmd *cmds)
{
	t_redirection	*redir;
	int				total;

	total = 0;
	redir = cmds->redirection;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->file)
			total++;
		redir = redir->next;
	}
	return (total);
}

void	ign_ctrl_c_with_exit_status(int pid, int *status, int *signal_detected)
{
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	g_exit = 130;
	if ((WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		|| (WIFEXITED(*status) && WEXITSTATUS(*status) == 130))
	{
		g_exit = 130;
		*signal_detected = 1;
		printf("\n");
		return ;
	}
}

void	unlink_files(int total_here_doc, char **files)
{
	int	i;

	i = 0;
	while (i < (total_here_doc - 1))
	{
		unlink(files[i]);
		i++;
	}
}