/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:24:20 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/25 14:54:09 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_word_value(char *input, int *i, t_quote_type *quote_type)
{
	int		start;
	char	quote;

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
		if (input[*i] == '|' || input[0] == '|' || input[*i] == '>'
			|| input[*i] == '<')
			return (NULL);
	}
	return (op);
}

int	handle_next_token(char *input, int *i, t_token **tokens)
{
	char			*value;
	t_quote_type	quote_type;
	t_type			type;

	quote_type = NO_QUOTE;
	if (input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		value = get_op(input, i);
	else
		value = get_word_value(input, i, &quote_type);
	if (!value)
		return (0);
	if (value[0] > 32 && ft_strlen(value) >= 1)
	{
		type = get_token_type(value);
		add_token_back(tokens, ft_lstnew_token(value, type, quote_type));
	}
	return (1);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] <= 32)
			i++;
		if (!input[i])
			break ;
		if (!handle_next_token(input, &i, &tokens))
			return (NULL);
	}
	return (tokens);
}
