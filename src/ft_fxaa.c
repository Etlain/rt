/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fxaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:02:51 by cguilbar          #+#    #+#             */
/*   Updated: 2017/03/09 11:34:03 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	apply(void *img, int w, int h, int emap[w][h])
{
	int		x;
	int		y;

	y = 1;
	while (y < h)
	{
		x = 1;
		while (x < w)
		{
			if (emap[x][y])
				ft_putpixel_img(img, x, y, emap[x][y]);
			++x;
		}
		++y;
	}
}

static int	blur(void *img, int x, int y)
{
	int		tc[3];
	int		cp;
	int		i;
	int		j;

	ft_bzero(tc, sizeof(*tc) * 3);
	j = -1;
	while (j <= 1)
	{
		i = -1;
		while (i <= 1)
		{
			cp = ft_getpixel(img, x + i, y + j);
			tc[0] += cp / 0x10000;
			tc[1] += cp % 0x10000 / 0x100;
			tc[2] += cp % 0x100;
			++i;
		}
		++j;
	}
	tc[0] /= 9;
	tc[1] /= 9;
	tc[2] /= 9;
	return (tc[0] * 0x10000 + tc[1] * 0x100 + tc[2]);
}

static int	aa_pixel(void *img, int x, int y)
{
	int		cp[5];

	cp[0] = ft_getpixel(img, x, y);
	cp[1] = ft_getpixel(img, x, y - 1);
	cp[2] = ft_getpixel(img, x + 1, y);
	cp[3] = ft_getpixel(img, x, y + 1);
	cp[4] = ft_getpixel(img, x - 1, y);
	if ((ft_rgbcmp(cp[0], cp[1]) < 0.75 || ft_rgbcmp(cp[0], cp[3]) < 0.75) &&\
			(ft_rgbcmp(cp[0], cp[2]) < 0.75 || ft_rgbcmp(cp[0], cp[4]) < 0.75))
		return (blur(img, x, y));
	return (cp[0]);
}

void		ft_fxaa(void *img, int w, int h, int i)
{
	int		x;
	int		y;
	int		emap[--w][--h];

	while (i > 0)
	{
		y = 1;
		while (y < h)
		{
			x = 1;
			while (x < w)
			{
				emap[x][y] = aa_pixel(img, x, y);
				++x;
			}
			++y;
		}
		apply(img, w, h, emap);
		--i;
	}
}
