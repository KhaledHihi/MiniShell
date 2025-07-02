/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anguenda <anguenda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:07 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/02 18:25:37 by anguenda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_unset(char **args, char **env, int is_created)
{
	int	i;
	int	var_index;
	int	is_found;

	i = 1;
	while (args && args[i])
	{
		if (has_equal_sign(args[i]))
		{
			is_found = search_for_env_var(env, args[i]);
			if (is_found || (is_found && is_created))
			{
				var_index = get_env_var_index(env, args[i]);
				while (env && env[var_index])
				{
					env[var_index] = env[var_index + 1];
					var_index++;
				}
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
