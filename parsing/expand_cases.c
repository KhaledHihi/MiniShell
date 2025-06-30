/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:44 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/30 19:04:33 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*case_of_var_with_exit_status(int *i, char *res)
{
	(*i) += 2;
	res = ft_strjoin(res, ft_itoa(g_exit));
	return (res);
}

char	*case_of_var_start_with_digit(char *word, int *i, char *res)
{
	(*i) += 2;
	while (word[*i])
		res = ft_strjoin_char(res, word[*i++]);
	return (res);
}

char	*case_of_quote_after_var(char *word, int *i, char *res, char quote_char)
{
	(*i)++;
	while (word[*i] && word[*i] != quote_char)
		res = ft_strjoin_char(res, word[(*i)++]);
	if (word[*i])
		(*i)++;
	return (res);
}

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

char	*double_quotes(const char *word, int *index, t_env *env, char *result)
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
