/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:51:15 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/19 15:24:17 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_char(char const *s1, char s2)
{
	int		i;
	int		j;
	char	*r;

	i = 0;
	j = 0;
	if (s1 == NULL)
		return (NULL);
	r = ft_malloc((ft_strlen(s1) + 2), 0);
	if (!r)
		return (NULL);
	while (s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	r[i++] = s2;
	r[i] = '\0';
	return (r);
}
