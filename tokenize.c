/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:24:20 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/11 20:02:47 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quote_value(char *input, int *i, t_quote_type *quote_type)
{
	char	quote;
	int		start;
	char	*value;

	*quote_type = NO_QUOTE;
	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	value = ft_substr(input, start, *i - start);
	if (input[*i] == quote)
		(*i)++;
	else
	{
		free(value);
		return (NULL);
	}
	if (quote == '\'')
		*quote_type = SINGLE_QUOTE;
	else if (quote == '"')
		*quote_type = DOUBLE_QUOTE;
	return (value);
}

char	*get_word_value(char *input, int *i, t_quote_type *quote_type)
{
	int	start;
	char quote;

	start = *i;
	while (input[*i] && (input[*i] != '|' && input[*i] != '>'
			&& input[*i] != '<') && input[*i] > 32)
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] != quote)
				return (NULL);
			if (quote == '\'')
				*quote_type = SINGLE_QUOTE;
			else if (quote == '"') 
				*quote_type = DOUBLE_QUOTE;
		}
		(*i)++;
	}
	return (ft_substr(input, start, *i - start));
}

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

char	*get_op(char *input, int *i)
{
	char	*op;

	if (!ft_strncmp(input + *i, ">>", 2) || !ft_strncmp(input + *i, "<<", 2))
	{
		op = ft_substr(input, *i, 2);
		*i += 2;
		if (input[*i] == '>' || input[*i] == '<')
			return (NULL);
	}
	else
	{
		op = ft_substr(input, *i, 1);
		*i += 1;
		if (input[*i] == '|')
			return (NULL);
	}
	return (op);
}

t_type	get_token_type(char *value)
{
	if (!ft_strncmp(value, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(value, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(value, "<<", 2))
		return (HEREDOC);
	else if (!ft_strncmp(value, ">", 1))
		return (REDIRECT_OUT);
	else if (!ft_strncmp(value, "<", 1))
		return (REDIRECT_IN);
	return (WORD);
}

t_token	*tokenize(char *input)
{
	t_token			*tokens;
	int				i;
	char			*value;
	t_quote_type	quote_type;
	t_type			type;

	type = 0;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		quote_type = 0;
		while (input[i] <= 32)
			i++;
		if (input[i] == '\0')
			break ;
		// if (input[i] == '\'' || input[i] == '"')
		// {
		// 	value = get_quote_value(input, &i, &quote_type);
		// 	if (!value)
		// 	{
		// 		tokens = NULL;
		// 		break ;
		// 	}
		// }
		else if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			value = get_op(input, &i);
			if (!value)
			{
				tokens = NULL;
				break ;
			}
		}
		else
		{
			value = get_word_value(input, &i, &quote_type);
			if (!value)
			{
				tokens = NULL;
				break ;
			}
		}
		if (value[0] > 32 && ft_strlen(value) >= 1)
		{
			type = get_token_type(value);
			add_token_back(&tokens, ft_lstnew_token(value, type, quote_type));
		}
	}
	return (tokens);
}
