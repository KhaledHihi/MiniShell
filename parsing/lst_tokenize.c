/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:41:50 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/17 12:43:49 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew_token(char *value, t_type type, t_quote_type quote)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 0);
	if (!new)
		return (NULL);
	new->value = value;
	new->token_type = type;
	new->quote_type = quote;
	new->next = NULL;
	return (new);
}

void	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}
