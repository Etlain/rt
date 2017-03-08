/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 13:04:43 by abara             #+#    #+#             */
/*   Updated: 2015/12/02 15:42:09 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char const *src, size_t n)
{
	int		index;
	int		i;

	index = 0;
	i = 0;
	while (dest[i])
	{
		i++;
	}
	while (*src != '\0' && index != n)
	{
		dest[i] = src[index];
		i++;
		index++;
	}
	dest[i] = '\0';
	return (dest);
}
