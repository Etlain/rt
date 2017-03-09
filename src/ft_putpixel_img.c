/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 13:42:09 by cguilbar          #+#    #+#             */
/*   Updated: 2017/03/09 11:34:54 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	ft_putpixel_img(void *img, int x, int y, int c)
{
	char	*pic;
	int		d;
	int		l;
	int		e;

	pic = mlx_get_data_addr(img, &d, &l, &e);
	ft_memcpy(pic + (x * d / 8) + (y * l), &c, d / 8);
}
