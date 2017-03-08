/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:32:31 by abara             #+#    #+#             */
/*   Updated: 2017/01/31 17:09:07 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_check_char(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ' && str[i] != c)
		i++;
	if (str[i] == c)
		return (1);
	else
		return (0);
}

double		ft_atod(char *str)
{
	double	val;
	double	tmp;
	int		power;
	int		i;

	i = 0;
	power = 1;
	val = (double)ft_atoi(str);
	while (str[i] != '.' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (val);
	tmp = (double)ft_atoi(&str[i + 1]);
	i = ft_strlen(&str[i + 1]);
	while (i-- > 0)
		power *= 10;
	tmp /= power;
	if (val > 0)
		val = val + tmp;
	else
		val = val - tmp;
	if (ft_check_char(str, '-') == 0 && val < 0)
		return (-val);
	return (val);
}
