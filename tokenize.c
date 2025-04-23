/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:24:20 by khhihi            #+#    #+#             */
/*   Updated: 2025/04/23 19:25:51 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_quote_value(char *input, int *i, t_quote_type *quote_type)
{
	char	quote;
	int		start;
	char	*value;

	quote = input[*i];
	(*i)++;
	start = *i;
	while(input[*i] && input[*i] != quote)
		i++;
	value = ft_substr(input, *i, *i - start);
	if (input[*i] == quote)
		(*i)++;
	if(quote == '\'')
		*quote_type = SINGLE_QUOTE;
	else if(quote == '"')
		*quote_type = DOUBLE_QUOTE;
	else
		*quote_type = NO_QUOTE;
	return (value);
}
char *get_word_value(char *input, int *i)
{
	int start;

	start = *i;
	while (input[*i] && input[*i] != '\'' && input[*i] > 32
			&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
			(*i)++;
	return (ft_substr(input, start, *i - start));
}
t_token *ft_lstnew_token(char *value, t_type type, t_quote_type quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if(!new)
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
t_token *tokenize(char *input)
{
	t_token *tokens;
	int 	i;
	char 	*value;
	t_quote_type quote_type;
	t_type	type;
	type = 0;

	tokens = NULL;
	i = 0;
	while(input[i])
	{
		while(input[i] <= 32)
			i++;
		if (input[i] == '\0')
			break;
		if (input[i] == '\'' || input[i] == '"')
			value = get_quote_value(input, &i, &quote_type);
		else
			value = get_word_value(input, &i);
		add_token_back(&tokens, ft_lstnew_token(value, type, quote_type));
	}
	print_node(tokens);
	return (tokens);
}
