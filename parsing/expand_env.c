/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:36:32 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/16 22:34:12 by khhihi           ###   ########.fr       */
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

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!strncmp(env->key, key, ft_strlen(key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// Function to handle single-quoted text
char	*handle_single_quotes(const char *word, int *index, char *result)
{
	(*index)++;
	while (word[*index] && word[*index] != '\'')
	{
		result = ft_strjoin_char(result, word[*index]);
		(*index)++;
	}
	if (word[*index])
		(*index)++;
	return (result);
}

// Function to handle environment variable expansion
char	*expand_env_variable(const char *word, int *index, t_env *env,
		char *result)
{
	int		start;
	char	*key;
	char	*value;

	start = ++(*index);
	while (word[*index] && (ft_isalnum(word[*index]) || word[*index] == '_'))
		(*index)++;
	key = ft_substr(word, start, *index - start);
	value = get_env_value(env, key);
	if (!value)
		value = ft_strdup("");
	free(key);
	for (int j = 0; value[j]; j++)
	{
		while (value[j] <= 32 && value[j + 1] <= 32)
			j++;
		result = ft_strjoin_char(result, value[j]);
	}
	return (result);
}

// Function to handle double-quoted text
char	*handle_double_quotes(const char *word, int *index, t_env *env,
		char *result)
{
	(*index)++;
	while (word[*index] && word[*index] != '"')
	{
		if (word[*index] == '$' && word[*index + 1] && (ft_isalnum(word[*index
					+ 1]) || word[*index + 1] == '_'))
			result = expand_env_variable(word, index, env, result);
		else
		{
			result = ft_strjoin_char(result, word[*index]);
			(*index)++;
		}
	}
	if (word[*index])
		(*index)++;
	return (result);
}

// Function to handle special cases like $? and $<number>
char	*handle_special_cases(const char *word, int *index, char *result)
{
	if (word[*index] == '$' && word[*index + 1] == '?')
	{
		(*index) += 2;
		result = ft_strjoin(result, ft_itoa(0));
	}
	else if (word[*index] == '$' && ft_isdigit(word[*index + 1]))
	{
		(*index) += 2;
	}
	return (result);
}

// Main function to expand variable values
char	*expand_variable_value(char *word, t_env *env, int *heredoc)
{
	int		i;
	char	*result;

	i = 0;
	if (*heredoc)
	{
		result = limiter(word);
		*heredoc = 0;
		return (result);
	}
	result = ft_strdup("");
	while (word[i])
	{
		if (word[i] == '\'')
			result = handle_single_quotes(word, &i, result);
		else if (word[i] == '$' && word[i + 1] && (ft_isalpha(word[i + 1])
				|| word[i + 1] == '_'))
			result = expand_env_variable(word, &i, env, result);
		else if (word[i + 1] && word[i] == '$' && word[i + 1] == '\'')
			result = case_of_squote_after_var(word, &i, result);
		else if (word[i + 1] && word[i] == '$' && word[i + 1] == '\"')
			result = case_of_dquote_after_var(word, &i, result);
		else if (word[i] == '"')
			result = handle_double_quotes(word, &i, env, result);
		// else if (word[i] == '$')
		// 	result = handle_special_cases(word, &i, result);
		else if (word[i] == '$' && word[i + 1] && word[i + 1] == '?')
			result = case_of_var_with_exit_status(&i, result);
		else if (word[i] == '$' && word[i + 1] && ft_isdigit(word[i + 1]))
			result = case_of_var_start_with_digit(word, &i, result);
		else
			result = ft_strjoin_char(result, word[i++]);
	}
	return (result);
}

// Expand variables and remove quotes for a list of tokens
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
				// Assume the old value is freed elsewhere
		}
		tokens = tokens->next;
	}
}
