/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 13:57:26 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/25 15:44:44 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_node(t_token *list)
{
	while (list)
	{
		printf("%s\n", list->value);
		printf("token_type : %d\n", list->token_type);
		printf("quote_type : %d\n", list->quote_type);
		printf("----------------------------\n");
		list = list->next;
	}
}

void	print_lst(t_env *list)
{
	while (list)
	{
		printf("lst key : %s\n", list->key);
		printf("lst value : %s\n", list->value);
		list = list->next;
	}
}

void	print_redirection_list(t_redirection *redir)
{
	printf("Redirections:\n");
	while (redir)
	{
		printf("  file: %s, type: %d, quote_type: %d\n",
			redir->file ? redir->file : "(null)", redir->type,
			redir->quote_type);
		redir = redir->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Command args: ");
		if (cmd->arg)
		{
			for (i = 0; cmd->arg[i]; ++i)
				printf("%s ", cmd->arg[i]);
		}
		printf("\n");
		printf("append: %d, heredoc: %d, heredoc_file: %s\n", cmd->append,
			cmd->heredoc, cmd->heredoc_file ? cmd->heredoc_file : "(null)");
		print_redirection_list(cmd->redirection);
		printf("----\n");
		cmd = cmd->next;
	}
}
