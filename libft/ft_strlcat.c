/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:21:23 by khhihi            #+#    #+#             */
/*   Updated: 2024/11/07 15:26:41 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize == 0 || dstsize < len_dst)
		return (len_src + dstsize);
	i = len_dst;
	while (*src && i < dstsize - 1)
		dst[i++] = *(src++);
	dst[i] = '\0';
	return (len_dst + len_src);
}
