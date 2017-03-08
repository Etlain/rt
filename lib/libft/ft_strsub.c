/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 15:19:55 by abara             #+#    #+#             */
/*   Updated: 2015/12/08 15:43:19 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tronc;
	size_t	index;

	index = 0;
	if (!s)
		return (NULL);
	tronc = (char *)malloc(sizeof(*tronc) * len + 1);
	if (tronc == NULL)
		return (NULL);
	while (s[start] && index < len)
	{
		tronc[index] = s[start];
		start++;
		index++;
	}
	tronc[index] = '\0';
	return (tronc);
}
