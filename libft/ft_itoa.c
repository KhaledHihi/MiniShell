/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:26:07 by khhihi            #+#    #+#             */
/*   Updated: 2024/11/03 21:37:58 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocate(int len, long nb)
{
	char	*s;

	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	if (nb == 0)
	{
		s[0] = '0';
		return (s);
	}
	else if (nb < 0)
	{
		nb = -nb;
		s[0] = '-';
	}
	while (nb)
	{
		s[--len] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*p;

	nb = n;
	len = 0;
	if (n == 0)
		len = 1;
	else if (n < 0)
		len = 1;
	while (n)
	{
		n = n / 10;
		len++;
	}
	p = ft_allocate(len, nb);
	return (p);
}
