/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 12:26:50 by abara             #+#    #+#             */
/*   Updated: 2015/12/09 12:18:35 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		size;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s) - 1;
	if (size > 0)
	{
		while (ft_isprint(s[size]) == 0 || s[size] == ' ')
			size--;
		while (ft_isprint(s[index]) == 0 || s[index] == ' ')
			index++;
	}
	size++;
	if (size < index)
		size = index;
	return (ft_strsub(s, index, size - index));
}
