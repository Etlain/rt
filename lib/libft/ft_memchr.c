/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:50:43 by abara             #+#    #+#             */
/*   Updated: 2015/11/30 12:44:03 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	i;
	unsigned char	*tab;

	tab = (unsigned char*)s;
	i = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (tab[index] == i)
			return (void *)(&tab[index]);
		index++;
	}
	return (NULL);
}
