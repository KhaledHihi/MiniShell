/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khhihi <khhihi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:55:58 by khhihi            #+#    #+#             */
/*   Updated: 2024/11/07 11:40:51 by khhihi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countw(char const *s1, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		while (s1[i] == c)
			i++;
		if (s1[i] && s1[i] != c)
			count++;
		while (s1[i] != c && s1[i])
			i++;
	}
	return (count);
}

static void	*free_arr(char **p, int r)
{
	while (r--)
		free(p[r]);
	free(p);
	return (NULL);
}

static char	*ft_alloc_word(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (ft_countw(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			arr[i] = ft_alloc_word(s, c);
			if (!arr[i])
				return (free_arr(arr, i));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
