/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 09:57:30 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 16:05:05 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void		set_vrep(t_v d, t_v *v)
{
	v[2] = normalize(d);
	if (fabs(v[2].y) == 1)
	{
		v[0].x = 1;
		v[1].z = -v[2].y;
		return ;
	}
	v[0].x = v[2].z;
	v[0].z = -v[2].x;
	v[0] = normalize(v[0]);
	v[1].y = sqrt(v[2].x * v[2].x + v[2].z * v[2].z);
	v[1].x = -v[2].x / (fabs(v[2].x) + fabs(v[2].z)) * v[2].y;
	v[1].z = -v[2].z / (fabs(v[2].x) + fabs(v[2].z)) * v[2].y;
	v[1] = normalize(v[1]);
}

double		limitation(double v, double min, double max)
{
	if (v > max)
		v = (double)((int)v % (int)max);
	if (v < min)
	{
		if (v < 0)
			v = v * (-1);
		v = (double)((int)v % (int)max);
	}
	return (v);
}

t_v			get_texel(t_texture t, int i, int j)
{
	t_v	color;

	color = set_v(0, 0, 0);
	if (i < 0 || j < 0)
		return (color);
	if (j * (t.w * 3) + (i * 3) < t.h * t.w * 3)
		color.x = t.texture[j * (t.w * 3) + (i * 3)];
	if (j * (t.w * 3) + (i * 3) + 1 < t.h * t.w * 3)
		color.y = t.texture[j * (t.w * 3) + (i * 3) + 1];
	if (j * (t.w * 3) + (i * 3) + 1 < t.h * t.w * 3)
		color.z = t.texture[j * (t.w * 3) + (i * 3) + 2];
	return (color);

}

static t_v	render_loop(t_winfo *w, int x, int y)
{
	double	ret;
	int		*nb;
	t_v		objcolor;

	t_v		d;
	t_v		uv;
	t_v		t;
	double	u;
	double	v;
	double	j;
	double	k;
	double	scale;

	nb = (int*)malloc(sizeof(int) * 2);
	nb[0] = w->file.nbobj;
	nb[1] = w->file.nblight;
	intersection(&w->ray, w->obj, w->file.nbobj);
	if (w->ray.id != -1)
	{
		objcolor = w->obj[w->ray.id].color;
		if ((w->obj[w->ray.id].type == 1 || w->obj[w->ray.id].type == 6 || w->obj[w->ray.id].type == 7 || w->obj[w->ray.id].type == 8) && w->text[w->ray.id].texture.texture != NULL)
		{
			d = normalize(get_v(w->obj[w->ray.id].a, w->ray.current));
			u = (0.5 + atan2(d.z, d.x) / (M_PI * 2)) + w->text[w->ray.id].d;
			v = acos(d.y) / (M_PI * 2);
			j = limitation(u * w->text[w->ray.id].texture.w, 0, w->text[w->ray.id].texture.w - 1);
			k = limitation(v * w->text[w->ray.id].texture.h, 0, w->text[w->ray.id].texture.h - 1);
			w->obj[w->ray.id].color = get_texel(w->text[w->ray.id].texture, j, k);
		}
		check_light(w, w->light, &w->ray, &w->obj[w->ray.id]);
		if (w->file.nblight == 0)
			w->ray.color = w->obj[w->ray.id].color;
		ret = shadow(w->light, w->ray, w->obj, nb);
		if (ret < w->opt.ambient)
			ret = w->opt.ambient;
		w->ray.color = limit_v(mult_v(w->ray.color, ret), 0, 255);
		w->obj[w->ray.id].color = objcolor;
		w->ray.color = reflection(w->ray, w, nb, w->opt.ref);
	}
	else
	{
		ft_memdel((void**)&nb);
		return (set_v(0, 0, 0));
	}
//	w->ray = reflection(w->ray.dir, w->ray, w->obj[w->ray.id]);
	ft_memdel((void**)&nb);
	return (w->ray.color);
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
	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			w->ray.a = w->cam.pos;
			w->ray.dir = normalize(add_v(add_v(mult_v(v[0], x - W / 2), mult_v(v[1], H / 
			2 - y)), mult_v(v[2], W / 2)));
			w->ray.id = -1;
			w->ray.t = -1;
			if (w->opt.sepia == 0)
				put_pixel(w, x, y, render_loop(w, x, y));
			else
				put_pixel_sepia(w, x, y, render_loop(w, x, y));
			++x;
		}
		++y;
	}
	if (w->opt.fxaa)
		ft_fxaa(w->img, W, H, w->opt.fxaa);
	ft_memdel((void**)&v);
	mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
}
