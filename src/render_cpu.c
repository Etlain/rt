/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 09:57:30 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 12:15:55 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static t_v	render_loop(t_winfo *w, int x, int y)
{
	double	ret;
	int		*nb;
	t_v		objcolor;

	intersection(&w->ray, w->obj, w->file.nbobj);
	if (w->ray.id != -1)
	{
		nb = (int*)malloc(sizeof(int) * 2);
		nb[0] = w->file.nbobj;
		nb[1] = w->file.nblight;
		objcolor = w->obj[w->ray.id].color;
		get_uv_texture(w);
		check_light(w, w->light, &w->ray, &w->obj[w->ray.id]);
		if (w->file.nblight == 0)
			w->ray.color = w->obj[w->ray.id].color;
		ret = shadow(w->light, w->ray, w->obj, nb);
		ret < w->opt.ambient ? ret = w->opt.ambient : 0;
		w->ray.color = limit_v(mult_v(w->ray.color, ret), 0, 255);
		w->obj[w->ray.id].color = objcolor;
		w->ray.color = reflection(w->ray, w, nb, w->opt.ref);
		ft_memdel((void**)&nb);
	}
	else
		return (set_v(0, 0, 0));
	return (w->ray.color);
}

static void	loop(t_winfo *w, int x, int y)
{
	w->ray.id = -1;
	w->ray.t = -1;
	if (w->opt.sepia == 0)
		put_pixel(w, x, y, render_loop(w, x, y));
	else
		put_pixel_sepia(w, x, y, render_loop(w, x, y));
}

void		render_cpu(t_winfo *w)
{
	int		x;
	int		y;
	t_v		*v;

	v = (t_v*)malloc(sizeof(t_v) * 3);
	v[0] = set_v(0, 0, 0);
	v[1] = set_v(0, 0, 0);
	v[2] = set_v(0, 0, 0);
	set_vrep(w->cam.dir, v);
	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			w->ray.a = w->cam.pos;
			w->ray.dir = normalize(add_v(add_v(mult_v(v[0], x - W / 2),
							mult_v(v[1], H / 2 - y)), mult_v(v[2], W / 2)));
			loop(w, x, y);
		}
	}
	if (w->opt.fxaa)
		ft_fxaa(w->img, W, H, w->opt.fxaa);
	ft_memdel((void**)&v);
	mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
}
