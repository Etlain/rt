/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:52:08 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 12:04:42 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

double		check_ellipsoid(t_ray *ray, t_object obj)
{
	double *pos;
	double *res;
	double *p;
	double a;

	p = (double*)malloc(sizeof(double) * 3);
	res = (double*)malloc(sizeof(double) * 2);
	pos = (double*)malloc(sizeof(double) * 3);
	pos[0] = ray->a.x - obj.a.x;
	pos[1] = ray->a.y - obj.a.y;
	pos[2] = ray->a.z - obj.a.z;
	p[0] = (ray->dir.x * ray->dir.x) / (obj.b.x * obj.b.x)
	+ (ray->dir.y * ray->dir.y) / (obj.b.y * obj.b.y)
	+ (ray->dir.z * ray->dir.z) / (obj.b.z * obj.b.z);
	p[1] = 2 * ((ray->dir.x * pos[0]) / (obj.b.x * obj.b.x)
	+ (ray->dir.y * pos[1]) / (obj.b.y * obj.b.y)
	+ (ray->dir.z * pos[2]) / (obj.b.z * obj.b.z));
	p[2] = (pos[0] * pos[0]) / (obj.b.x * obj.b.x)
	+ (pos[1] * pos[1]) / (obj.b.y * obj.b.y)
	+ (pos[2] * pos[2]) / (obj.b.z * obj.b.z) - 1;
	a = ft_condition(res, degree_2(p, res));
	free(pos);
	free(p);
	free(res);
	return (a);
}

t_v			normal_ellipsoid(t_ray *ray, t_object *obj)
{
	t_v		res;
	double	*pos;

	pos = (double*)malloc(sizeof(double) * 3);
	pos[0] = ray->a.x - obj->a.x;
	pos[1] = ray->a.y - obj->a.y;
	pos[2] = ray->a.z - obj->a.z;
	res.x = ray->dir.x * ray->t + pos[0];
	res.y = ray->dir.y * ray->t + pos[1];
	res.z = ray->dir.z * ray->t + pos[2];
	res.x *= 2 / obj->b.x * obj->b.x;
	res.y *= 2 / obj->b.y * obj->b.y;
	res.z *= 2 / obj->b.z * obj->b.z;
	free(pos);
	return (res);
}
