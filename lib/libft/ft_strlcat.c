/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:12:09 by abara             #+#    #+#             */
/*   Updated: 2015/12/07 14:26:00 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		index;
	int		x;

	x = 0;
	index = 0;
	while (dst[x] != '\0' && x < size)
		x++;
	while (src[index] != '\0' && x + index < size - 1)
	{
		dst[x + index] = src[index];
		index++;
	}
	if (x + index < size)
		dst[x + index] = '\0';
	return (ft_strlen(src) + x);
}
