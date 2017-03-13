/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:09:12 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 14:36:50 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

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

static void	get_uv_texture_help(t_winfo *w)
{
	t_v		x;
	t_v		d;
	t_uv	v;

	if ((w->obj[w->ray.id].type == 2 || w->obj[w->ray.id].type == 4)
	&& w->text[w->ray.id].texture.texture != NULL)
	{
		x.z = 10;
		w->ray.current = add_v(w->ray.a, mult_v(w->ray.dir, w->ray.t));
		d = get_v(w->ray.current, v_mult_v(w->obj[w->ray.id].a,
		w->obj[w->ray.id].b));
		x.x = 0.5 + atan2(d.z, d.x) / M_PI * 0.5;
		x.y = d.y / x.z;
		x.y = x.y - floor(x.y);
		v.k = limitation(x.x * w->text[w->ray.id].texture.w, 0,
		w->text[w->ray.id].texture.w - 1);
		v.j = limitation(x.y * w->text[w->ray.id].texture.h, 0,
		w->text[w->ray.id].texture.h - 1);
		w->obj[w->ray.id].color = get_texel(w->text[w->ray.id].texture,
		v.k, v.j);
	}
}

void		get_uv_texture(t_winfo *w)
{
	t_uv	uv;

	if ((w->obj[w->ray.id].type == 1 || w->obj[w->ray.id].type == 6
	|| w->obj[w->ray.id].type == 7 || w->obj[w->ray.id].type == 8)
	&& w->text[w->ray.id].texture.texture != NULL)
	{
		uv.d = normalize(get_v(w->obj[w->ray.id].a, w->ray.current));
		uv.u = (0.5 + atan2(uv.d.z, uv.d.x) / (M_PI * 2));
		uv.v = acos(uv.d.y) / (M_PI * 2);
		uv.j = limitation(uv.u * w->text[w->ray.id].texture.w,
		0, w->text[w->ray.id].texture.w - 1);
		uv.k = limitation(uv.v * w->text[w->ray.id].texture.h,
		0, w->text[w->ray.id].texture.h - 1);
		w->obj[w->ray.id].color = get_texel(w->text[w->ray.id].texture,
		uv.j, uv.k);
	}
	get_uv_texture_help(w);
}

t_v			get_uv_normal(t_winfo *w, t_v n)
{
	t_uv	uv;
	t_v		color;

	if ((w->obj[w->ray.id].type == 1 || w->obj[w->ray.id].type == 6
	|| w->obj[w->ray.id].type == 7 || w->obj[w->ray.id].type == 8)
	&& w->text[w->ray.id].normal.texture != NULL)
	{
		uv.d = normalize(get_v(w->obj[w->ray.id].a, w->ray.current));
		uv.u = (0.5 + atan2(uv.d.z, uv.d.x) / (M_PI * 2))
			+ w->text[w->ray.id].d;
		uv.v = acos(uv.d.y) / (M_PI * 2);
		uv.j = limitation(uv.u * w->text[w->ray.id].normal.w,
		0, w->text[w->ray.id].normal.w - 1);
		uv.k = limitation(uv.v * w->text[w->ray.id].normal.h,
		0, w->text[w->ray.id].normal.h - 1);
		color = get_texel(w->text[w->ray.id].normal,
		uv.j, uv.k);
		n = apply_nmap(n, color);
	}
	return (n);
}
