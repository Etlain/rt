/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:49:44 by abara             #+#    #+#             */
/*   Updated: 2015/12/08 15:34:37 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*map;

	index = 0;
	if (!s)
		return (NULL);
	map = (char*)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (map == NULL)
		return (NULL);
	while (s[index] != '\0')
	{
		map[index] = f(index, s[index]);
		index++;
	}
	map[index] = '\0';
	return (map);
}
