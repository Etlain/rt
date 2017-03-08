/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:08:39 by cguilbar          #+#    #+#             */
/*   Updated: 2017/01/25 12:50:29 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

int		ft_getpixel(void *img, int x, int y)
{
	char	*pic;
	int		d;
	int		l;
	int		e;

	pic = mlx_get_data_addr(img, &d, &l, &e);
	return (*(unsigned int*)(pic + (x * d / 8) + (y * l)));
}
