/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrncpy_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:57:35 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/13 12:57:56 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

unsigned char			*ft_ustrncpy_f(unsigned char *dest,
		const unsigned char *src, size_t n)
{
	int					index;
	int					i;

	index = 0;
	ft_bzero(dest, n);
	while (index != n)
	{
		dest[index] = src[index];
		index++;
	}
	return (dest);
}
