/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:12:01 by abara             #+#    #+#             */
/*   Updated: 2015/11/30 12:51:07 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int				index;
	unsigned char	*tab;

	index = 0;
	tab = s;
	while (index < n)
	{
		tab[index] = (unsigned char)c;
		index++;
	}
	return (s);
}
