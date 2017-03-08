/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:37:23 by abara             #+#    #+#             */
/*   Updated: 2015/12/02 13:44:29 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	size_t		index;

	index = ft_strlen(dest);
	while (*src)
	{
		dest[index] = *src;
		index++;
		src++;
	}
	dest[index] = '\0';
	return (dest);
}
