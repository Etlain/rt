/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 09:50:33 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:32:12 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	put_pixel(t_winfo *w, int x, int y, t_v color)
{
	int	index;

	index = (y * (W * 4)) + x * 4;
	if ((x >= 0 && x <= W) && (y >= 0 && y <= H))
	{
		w->data[index] = (unsigned char)color.x;
		w->data[index + 1] = (unsigned char)color.y;
		w->data[index + 2] = (unsigned char)color.z;
		w->data[index + 3] = 0;
	}
}

void	put_pixel_sepia(t_winfo *w, int x, int y, t_v color)
{
	t_v	c;
	int	index;

	index = (y * (W * 4)) + x * 4;
	if ((x >= 0 && x <= W) && (y >= 0 && y <= H))
	{
		c.x = ((color.x * 0.272) +
		(color.y * 0.534) + (color.z * 0.131));
		c.y = ((color.x * 0.349) +
		(color.y * 0.686) + (color.z * 0.168));
		c.z = ((color.x * 0.393) +
		(color.y * 0.769) + (color.z * 0.189));
		c = limit_v(c, 0, 255);
		w->data[index] = (unsigned char)c.x;
		w->data[index + 1] = (unsigned char)c.y;
		w->data[index + 2] = (unsigned char)c.z;
		w->data[index + 3] = 0;
	}
}

void	draw_console(t_winfo *w, t_v color)
{
	int	a;
	int	b;
	int	c;
	int	d;

	a = 0;
	b = H - 20;
	c = W;
	d = H;
	while (b != d)
	{
		a = 0;
		while (a != c)
		{
			put_pixel(w, a, b, color);
			a++;
		}
		b++;
	}
}
