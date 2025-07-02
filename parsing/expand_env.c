/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:36:32 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/02 15:31:16 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*limiter(char *limiter)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (limiter[i] && limiter)
	{
		if (limiter[i] == '\'' || limiter[i] == '"')
		{
			quote = limiter[i++];
			while (limiter[i] && limiter[i] != quote)
				result = ft_strjoin_char(result, limiter[i++]);
			i++;
		}
		else
			result = ft_strjoin_char(result, limiter[i++]);
	}
	return (result);
}

char	*expand_env_variable(const char *word, int *i, t_env *env, char *result)
{
	int (start), (j);
	char *(key), *(value);
	(*i)++;
	start = (*i);
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		(*i)++;
	key = ft_substr(word, start, (*i) - start);
	value = get_env_value(env, key);
	if (!value)
		value = ft_strdup("");
	j = 0;
	while (value && value[j])
	{
		result = ft_strjoin_char(result, value[j]);
		j++;
	}
	return (result);
}

static char	*process_expansion_case(char *word, int *i, t_env *env, char *res)
{
	if (word[*i] == '\'')
		return (handle_single_quotes(word, i, res));
	if (word[*i] == '$' && word[*i + 1] && (ft_isalpha(word[*i + 1]) || word[*i
				+ 1] == '_'))
		return (expand_env_variable(word, i, env, res));
	if (word[*i] == '$' && (word[*i + 1] == '\'' || word[*i + 1] == '"'))
		return (case_of_quote_after_var(word, i, res, word[*i + 1]));
	if (word[*i] == '$' && word[*i + 1] == '?')
		return (case_of_var_with_exit_status(i, res));
	if (word[*i] == '"')
		return (double_quotes(word, i, env, res));
	if (word[*i] == '$' && ft_isdigit(word[*i + 1]))
		return (case_of_var_start_with_digit(word, i, res));
	return (ft_strjoin_char(res, word[(*i)++]));
}

char	*expand_variable_value(char *word, t_env *env, int *heredoc)
{
	int		i;
	char	*res;

	i = 0;
	if (*heredoc)
	{
		res = limiter(word);
		*heredoc = 0;
		return (res);
	}
	res = ft_strdup("");
	while (word[i])
		res = process_expansion_case(word, &i, env, res);
	return (res);
}

void	expand_variables_and_remove_quotes(t_token *tokens, t_env *env)
{
	char	*expanded_value;
	int		heredoc;

	heredoc = 0;
	while (tokens)
	{
		if (tokens->token_type == HEREDOC)
			heredoc = 1;
		if (tokens->token_type == WORD)
		{
			expanded_value = expand_variable_value(tokens->value, env,
					&heredoc);
			tokens->value = expanded_value;
		}
		tokens = tokens->next;
	}
}
