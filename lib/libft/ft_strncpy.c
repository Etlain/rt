/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 12:09:29 by abara             #+#    #+#             */
/*   Updated: 2015/12/07 13:52:37 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int		index;

	index = 0;
	ft_bzero(dest, n);
	while (src[index] != '\0' && index != n)
	{
		dest[index] = src[index];
		index++;
	}
	return (dest);
}
