/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:37:13 by khhihi            #+#    #+#             */
/*   Updated: 2025/06/20 10:52:12 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**realoc_arr(char **arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	i = 0;
	len = 0;
	new_arr = NULL;
	while (arr && arr[len])
		len++;
	new_arr = ft_malloc(sizeof(char *) * (len + 2), 0);
	if (!new_arr)
		return (NULL);
	while (len > i)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(str);
	new_arr[++i] = NULL;
	free(arr);
	return (new_arr);
}
