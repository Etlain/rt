/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 09:13:52 by abara             #+#    #+#             */
/*   Updated: 2015/12/02 16:09:29 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		index;
	int		x;
	int		y;

	x = 0;
	if (s2[0] == '\0')
		return (char*)(s1);
	while (s1[x] != '\0')
	{
		y = 0;
		index = x;
		while (s1[index] == s2[y])
		{
			y++;
			index++;
			if (s2[y] == '\0')
				return (char*)(&s1[x]);
		}
		x++;
	}
	return (NULL);
}
