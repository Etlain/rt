/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:08:39 by cguilbar          #+#    #+#             */
/*   Updated: 2017/03/09 11:34:13 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

int		ft_getpixel(void *img, int x, int y)
{
	char	*pic;
	int		d;
	int		l;
	int		e;

	pic = mlx_get_data_addr(img, &d, &l, &e);
	return (*(unsigned int*)(pic + (x * d / 8) + (y * l)));
}
