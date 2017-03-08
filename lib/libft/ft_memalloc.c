/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:04:30 by abara             #+#    #+#             */
/*   Updated: 2015/11/29 12:55:57 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*tab;

	tab = malloc(size);
	if (tab == NULL)
	{
		return (NULL);
	}
	ft_memset(tab, 0, size);
	return (tab);
}
