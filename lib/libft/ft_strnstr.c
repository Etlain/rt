/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 17:09:37 by abara             #+#    #+#             */
/*   Updated: 2015/12/07 14:12:28 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		x;
	size_t		y;

	if (*s2 == '\0')
		return ((char*)s1);
	x = 0;
	y = 0;
	while (s1[x] != '\0')
	{
		while (s2[y] == s1[x + y] && x + y < n)
		{
			y++;
			if (s2[y] == '\0')
				return ((char*)s1 + x);
		}
		x++;
		y = 0;
	}
	return (NULL);
}
