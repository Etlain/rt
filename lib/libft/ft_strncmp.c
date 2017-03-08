/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:37:02 by abara             #+#    #+#             */
/*   Updated: 2015/12/07 16:35:50 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (s1[index] != '\0' && s2[index] != '\0' && index < n - 1)
	{
		if (s1[index] != s2[index])
			break ;
		index++;
	}
	return (unsigned int)((unsigned char)s1[index] - (unsigned char)s2[index]);
}
