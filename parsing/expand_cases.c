/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:44 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/16 22:27:41 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*case_of_var_with_exit_status(int *i, char *res)
{
	(*i)+= 2;
	res = ft_strjoin(res, ft_itoa(g_exit));
	return (res);
}

char	*case_of_var_start_with_digit(char *word,int *i,char *res)
{
	(*i) += 2;
	while(word[*i])
		res = ft_strjoin_char(res, word[*i++]);
	return (res);
}

char	*case_of_squote_after_var(char *word, int *i, char *res)
{
	(*i)++;
	while (word[*i] && word[*i] != '\'')
		res = ft_strjoin_char(res, word[*i++]);
	if (word[*i])
		(*i)++;
	return (res);
}

char	*case_of_dquote_after_var(char *word, int *i, char *result)
{
	(*i)++;
	while (word[*i] && word[*i] != '\"')
		result = ft_strjoin_char(result, word[*i++]);
	if (word[*i])
		(*i)++;
	return (result);
}
