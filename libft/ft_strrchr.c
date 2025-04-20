/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:31:56 by khhihi            #+#    #+#             */
/*   Updated: 2024/11/03 18:21:25 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (s[e])
		e++;
	while (i <= e)
	{
		if (s[e] == (char)c)
			return ((char *)s + e);
		e--;
	}
	return (NULL);
}
