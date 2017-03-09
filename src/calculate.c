/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 15:06:44 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:31:08 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

double	check_sphere(t_ray *ray, t_object obj)
{
	double	a;
	double	b;
	double	c;

	a = (ray->dir.x * ray->dir.x) + (ray->dir.y * ray->dir.y) +
	(ray->dir.z * ray->dir.z);
	b = 2 * (ray->dir.x * (ray->a.x - obj.a.x) + ray->dir.y *
	(ray->a.y - obj.a.y) + ray->dir.z * (ray->a.z - obj.a.z));
	c = (ray->a.x - obj.a.x) * (ray->a.x - obj.a.x) +
	(ray->a.y - obj.a.y) * (ray->a.y - obj.a.y) +
	(ray->a.z - obj.a.z) * (ray->a.z - obj.a.z) - (obj.r * obj.r);
	return (get_t_a((b * b) - 4 * a * c, a, b));
}

double	check_cylinder(t_ray *ray, t_object obj)
{
	t_v		v;
	double	a;
	double	b;
	double	c;
	double	delta;

	obj.b = normalize(obj.b);
	v = get_v(obj.a, ray->a);
	a = dot(ray->dir, ray->dir) - dpower(dot(ray->dir, obj.b), 2);
	b = 2 * (dot(ray->dir, v) - dot(ray->dir, obj.b) * dot(v, obj.b));
	c = dot(v, v) - dpower(dot(v, obj.b), 2) - (obj.r * obj.r);
	delta = get_t_a((b * b) - 4 * a * c, a, b);
	if (delta >= 0.1)
		return (delta);
	return (-1);
}

double	check_plane(t_ray *ray, t_object *obj)
{
	t_v		v;
	t_v		o;
	double	t;
	double	d;

	o = set_v(0, 0, 0);
	v = get_v(o, obj->a);
	obj->c = normalize(obj->c);
	d = norm_v(v);
	t = -(obj->c.x * ray->a.x + obj->c.y * ray->a.y +
	obj->c.z * ray->a.z + d) / (obj->c.x * ray->dir.x +
	obj->c.y * ray->dir.y + obj->c.z * ray->dir.z);
	if (t >= 0.001)
		return (t);
	return (-1);
}

double	check_cone(t_ray *ray, t_object obj)
{
	t_v		x;
	double	a;
	double	b;
	double	c;
	double	k;

	obj.b = normalize(obj.b);
	x = get_v(obj.a, ray->a);
	k = tan((obj.r / 2) / (180 / M_PI));
	a = dot(ray->dir, ray->dir) - (1 + k * k) *
	dpower(dot(ray->dir, obj.b), 2);
	b = 2 * (dot(ray->dir, x) - ((1 + k * k) *
	dot(ray->dir, obj.b) * dot(x, obj.b)));
	c = dot(x, x) - ((1 + k * k) * dpower(dot(x, obj.b), 2));
	c = (b * b) - 4 * a * c;
	k = get_t_a(c, a, b);
	if (k >= 0.01)
		return (k);
	return (-1);
}

double	check_triangle(t_ray *ray, t_object *obj)
{
	t_v		p;
	double	det;
	double	u;
	double	v;
	double	t;

	p = cross(ray->dir, get_v(obj->a, obj->c));
	det = dot(get_v(obj->a, obj->b), p);
	if (det > -0.000001 && det < 0.000001)
		return (-1);
	det = 1.0 / det;
	u = dot(get_v(obj->a, ray->a), p) * det;
	if (u < 0 || u > 1.0)
		return (-1);
	p = cross(get_v(obj->a, ray->a), get_v(obj->a, obj->b));
	v = dot(ray->dir, p) * det;
	if (v < 0 || u + v > 1.0)
		return (-1);
	t = dot(get_v(obj->a, obj->c), p) * det;
	if (t > 0.000001)
		return (t);
	return (-1);
}
