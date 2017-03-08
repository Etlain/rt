/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:37:44 by abara             #+#    #+#             */
/*   Updated: 2015/12/08 15:24:10 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*map;
	size_t	index;

	index = 0;
	if (!s)
		return (NULL);
	map = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (map == NULL)
		return (NULL);
	while (s[index] != '\0')
	{
		map[index] = f(s[index]);
		index++;
	}
	map[index] = '\0';
	return (map);
}
