/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:54:06 by abara             #+#    #+#             */
/*   Updated: 2015/12/07 15:45:27 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*strdst;
	unsigned char	*strsrc;
	size_t			index;

	index = 0;
	strdst = dst;
	strsrc = (unsigned char*)src;
	while (index < n)
	{
		strdst[index] = strsrc[index];
		if (strsrc[index] == (unsigned char)c)
			return (&strdst[index + 1]);
		index++;
	}
	return (NULL);
}
