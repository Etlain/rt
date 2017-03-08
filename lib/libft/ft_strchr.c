/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:45:54 by abara             #+#    #+#             */
/*   Updated: 2015/12/02 14:41:25 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		index;
	char	i;
	char	*str;

	index = 0;
	str = (char*)s;
	i = (char)c;
	while (str[index] != '\0')
	{
		if (str[index] == i)
			return (&str[index]);
		index++;
	}
	if (c == '\0')
		return (&str[index]);
	return (NULL);
}
