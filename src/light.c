/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:53:50 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 12:50:09 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void		get_normal(t_ray *ray, t_object *obj)
{
	double	c;

	if (obj->type == 1)
		obj->c = get_v(obj->a, ray->current);
	else if (obj->type == 2)
	{
		c = norm_v(get_v(obj->a, ray->current)) * dot(normalize(obj->b),
		normalize(get_v(obj->a, ray->current)));
		obj->c = add_v(mult_v(obj->b, -c), get_v(obj->a, ray->current));
	}
	else if (obj->type == 4)
	{
		c = norm_v(get_v(obj->a, ray->current)) / dot(normalize(obj->b),
		normalize(get_v(obj->a, ray->current)));
		obj->c = add_v(mult_v(obj->b, -c), get_v(obj->a, ray->current));
	}
	if (obj->type == 6)
		obj->c = normal_torus(ray, obj);
	else if (obj->type == 7)
		obj->c = normal_ct(ray, obj);
	else if (obj->type == 8)
		obj->c = normal_ellipsoid(ray, obj);
}

t_v			get_normal_other(t_ray *ray, t_object *obj, t_light l)
{
	t_v n;

	n = cross(get_v(obj->b, obj->a), get_v(obj->c, obj->a));
	if (dot(n, get_v(l.pos, ray->current)) > 0)
		n = invert_v(n);
	return (n);
}

static void	get_specular(t_ray *ray, t_light l, t_v n)
{
	t_v		r;
	t_v		lp;
	double	d;

	lp = get_v(l.pos, ray->current);
	lp = normalize(lp);
	r = add_v(lp, mult_v(mult_v(n, 2), dot(invert_v(n), lp)));
	r = normalize(r);
	d = dot(invert_v(lp), r);
	d = dpower(d, 100);
	if (d > 0)
	{
		ray->color = add_v(ray->color, mult_v(ray->color, d));
	}
}

static void	light(t_winfo *w, t_light l, t_ray *ray, t_object *obj)
{
	t_v		v;
	t_v		n;
	double	d;

	ray->color = add_v(obj->color, l.color);
	ray->current = add_v(ray->a, mult_v(ray->dir, ray->t));
	v = get_v(ray->current, l.pos);
	v = normalize(v);
	get_normal(ray, obj);
	n = set_v(obj->c.x, obj->c.y, obj->c.z);
	if (obj->type == 5)
		n = get_normal_other(ray, obj, l);
	n = get_uv_normal(w, n);
	n = normalize(n);
	d = dot(v, n);
	if (d < w->opt.ambient || d > 1)
		d = w->opt.ambient;
	if (w->opt.cshade > 0)
	{
		d = (double)((int)(d * w->opt.cshade));
		d /= w->opt.cshade;
	}
	ray->color = mult_v(ray->color, d);
	if (w->opt.ambient == 0)
		get_specular(ray, l, n);
}

void		check_light(t_winfo *w, t_light *l, t_ray *ray, t_object *obj)
{
	t_v		color;
	double	part;
	int		i;

	i = 0;
	if (w->file.nblight != 0)
		part = (double)(1 / (double)w->file.nblight);
	else
		part = 0;
	color = set_v(0, 0, 0);
	while (i < w->file.nblight)
	{
		light(w, l[i], ray, obj);
		color = add_v(color, ray->color);
		color = mult_v(color, 0.75);
		i++;
	}
	ray->color = limit_v(color, 0, 255);
}
