/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:34:08 by abara             #+#    #+#             */
/*   Updated: 2017/02/24 14:41:24 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dtoa(double d)
{
	char	*dst;
	double	n;
	int		check;
	int		power;

	power = 0;
	check = 0;
	dst = ft_itoa((int)d);
	if (d < 0)
	{
		d = -d;
		check = 1;
	}
	d = d - (int)d;
	n = d - (int)d;
	while (n > 0.000001 || n < -0.000001)
	{
		n /= 10;
		power++;
	}
	if (dst[0] == '0' && check == 1)
		dst = ft_strjoin("-", dst);
	dst = ft_strjoin(dst, ".");
	dst = ft_strjoin(dst, ft_itoa(d * ft_power(10, power)));
	return (dst);
}
