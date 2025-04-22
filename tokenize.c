/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:24:20 by khhihi            #+#    #+#             */
/*   Updated: 2025/04/22 19:28:05 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char get_quote_value(char *input, int *i, t_quote_type *quote_type)
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
		(*i++);
	if(quote == '\'')
		*quote_type = SINGLE_QUOTE;
	else if(quote == '"')
		*quote_type = DOUBLE_QUOTE;
	else
		*quote_type = NO_QUOTE;
	return value;
}
char get_word_value(char *input, int *i)
{
	int start;
	char *value;

}

t_token *tokenize(char *input)
{
	t_token *tokens;
	int 	i;
	char 	*value;
	t_quote_type quote_type;

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
	}
}
