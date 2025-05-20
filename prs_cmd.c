/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:09:54 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/20 15:00:18 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd), 0);
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_cmd));
	return (new);
}

void	add_cmd_to_lst(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void add_redirections(t_cmd *current_cmd,t_redirection *new_redir)
{
	t_redirection	*lst;

	if (!current_cmd->redirection)
		current_cmd->redirection = new_redir;
	else
	{
		lst = current_cmd->redirection;
		while(lst->next)
			lst = lst->next;
		lst->next = new_redir;
	}
}

static int	handle_redirection(t_cmd *current_cmd, t_token **tokens)
{
	t_redirection	*new_redir;
	new_redir = ft_malloc(sizeof(t_redirection), 0);
	if (!new_redir)
	return (0);
	ft_bzero(new_redir, sizeof(t_redirection));
	new_redir->type = (*tokens)->token_type;
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || (*tokens)->token_type == REDIRECT_IN
	|| (*tokens)->token_type == REDIRECT_OUT
	|| (*tokens)->token_type == APPEND || (*tokens)->token_type == HEREDOC)
	return (0);
	new_redir->file = ft_strdup((*tokens)->value);
	add_redirections(current_cmd, new_redir);
	if (new_redir->type == APPEND)
		current_cmd->append = 1;
	else if (new_redir->type == HEREDOC)
		current_cmd->heredoc = 1;
	return (1);
}

t_cmd	*prs_cmd(t_token *tokens)
{
	t_cmd	*cmd_lst;
	t_cmd	*curr_cmd;

	cmd_lst = NULL;
	curr_cmd = NULL;
	while (tokens)
	{
		if (!curr_cmd || tokens->token_type == PIPE)
		{
			curr_cmd = create_new_cmd();
			if (!curr_cmd)
				return (NULL);
			add_cmd_to_lst(&cmd_lst, curr_cmd);
		}
		if (tokens->token_type == WORD)
			curr_cmd->arg = realoc_arr(curr_cmd->arg, tokens->value);
		else if (tokens->token_type == REDIRECT_IN
			|| tokens->token_type == REDIRECT_OUT
			|| tokens->token_type == APPEND || tokens->token_type == HEREDOC)
			if(!handle_redirection(curr_cmd, &tokens))
				return (NULL);
		tokens = tokens->next;
	}
	return (cmd_lst);
}
