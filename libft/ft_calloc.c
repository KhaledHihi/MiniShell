/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:17:07 by khhihi            #+#    #+#             */
/*   Updated: 2025/05/09 18:26:06 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	if (size && count > SIZE_MAX / size)
		return (NULL);
	p = ft_malloc(count * size, 0);
	if (!p)
		return (NULL);
	while (i < size * count)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
