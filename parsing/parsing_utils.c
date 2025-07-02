/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:49:45 by khhihi            #+#    #+#             */
/*   Updated: 2025/07/02 17:12:07 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd), 0);
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_cmd));
	return (new);
}

void	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg && msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

int	only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 32)
			return (0);
		i++;
	}
	return (1);
}

int	check_unvalide_cmds_error(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->token_type == PIPE && tmp->next == NULL)
			return (0);
		if (tmp->token_type == PIPE)
		{
			tmp = tmp->next;
			if (tmp->token_type == PIPE)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*case_of_word(char *word, int *i, char *result)
{
	result = ft_strjoin_char(result, word[*i]);
	(*i)++;
	return (result);
}
