/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 10:58:50 by abara             #+#    #+#             */
/*   Updated: 2016/12/06 11:19:33 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	float	val;
	float	tmp;
	int		power;
	int		i;

	i = 0;
	power = 1;
	val = (float)ft_atoi(str);
	while (str[i] != '.' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (val);
	tmp = (float)ft_atoi(&str[i + 1]);
	i = ft_strlen(&str[i + 1]);
	while (i-- > 0)
		power *= 10;
	tmp /= power;
	if (val > 0)
		val = val + tmp;
	else
		val = val - tmp;
	return (val);
}
