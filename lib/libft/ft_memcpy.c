/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:35:14 by abara             #+#    #+#             */
/*   Updated: 2015/12/02 12:25:34 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*strdst;
	unsigned char	*strsrc;
	size_t			index;

	index = 0;
	strdst = (unsigned char*)dst;
	strsrc = (unsigned char*)src;
	while (index < n)
	{
		strdst[index] = strsrc[index];
		index++;
	}
	return (dst);
}
