/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:50:13 by abara             #+#    #+#             */
/*   Updated: 2015/11/29 12:43:09 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		size;
	char	i;
	char	*str;

	str = (char*)s;
	i = (char)c;
	size = ft_strlen(s);
	while (size >= 0)
	{
		if (str[size] == i)
			return (&str[size]);
		size--;
	}
	return (NULL);
}
