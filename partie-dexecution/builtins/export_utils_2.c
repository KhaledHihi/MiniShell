/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:44:18 by anguenda          #+#    #+#             */
/*   Updated: 2025/07/01 22:11:20 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../minishell.h"

int	ft_get_env_len(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}

int	ft_get_env_var_len(char *env_var)
{
	int	count;

	count = 0;
	while (env_var[count] && env_var[count] != '=')
		count++;
	return (count);
}

int	ft_max(int value1, int value2)
{
	if (value1 > value2)
		return (value1);
	return (value2);
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
