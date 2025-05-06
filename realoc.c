/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:37:13 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/03 16:36:31 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **realoc_arr(char **arr, char *str)
{
	int i = -1;
	int len = 0;
	char **new_arr;

	while(arr && arr[len])
		len++;
	new_arr = malloc(sizeof(char *) * len + 2);
	if (!new_arr)
		return (NULL);
	while (len > ++i)
		new_arr[i] = arr[i];
	new_arr[i] = ft_strdup(str);
	new_arr[++i] = NULL;
	free(arr);
	return (new_arr);
}
