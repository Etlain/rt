/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:09:12 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 17:52:54 by abara            ###   ########.fr       */
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

t_v		get_texel(t_texture t, int i, int j)
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

void	get_uv_texture(t_winfo *w)
{
	t_uv	uv;

	if ((w->obj[w->ray.id].type == 1 || w->obj[w->ray.id].type == 6
	|| w->obj[w->ray.id].type == 7 || w->obj[w->ray.id].type == 8)
	&& w->text[w->ray.id].texture.texture != NULL)
	{
		uv.d = normalize(get_v(w->obj[w->ray.id].a, w->ray.current));
		uv.u = (0.5 + atan2(uv.d.z, uv.d.x) / (M_PI * 2)) + w->text[w->ray.id].d;
		uv.v = acos(uv.d.y) / (M_PI * 2);
		uv.j = limitation(uv.u * w->text[w->ray.id].texture.w,
		0, w->text[w->ray.id].texture.w - 1);
		uv.k = limitation(uv.v * w->text[w->ray.id].texture.h,
		0, w->text[w->ray.id].texture.h - 1);
		w->obj[w->ray.id].color = get_texel(w->text[w->ray.id].texture,
		uv.j, uv.k);
	}
}

t_v		get_uv_normal(t_winfo *w, t_v n)
{
	t_uv	uv;
	t_v		color;

	if ((w->obj[w->ray.id].type == 1 || w->obj[w->ray.id].type == 6
	|| w->obj[w->ray.id].type == 7 || w->obj[w->ray.id].type == 8)
	&& w->text[w->ray.id].normal.texture != NULL)
	{
		uv.d = normalize(get_v(w->obj[w->ray.id].a, w->ray.current));
		uv.u = (0.5 + atan2(uv.d.z, uv.d.x) / (M_PI * 2)) + w->text[w->ray.id].d;
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
