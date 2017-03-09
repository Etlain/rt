/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:05:20 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:43:25 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

double			ft_condition(double *res, int max)
{
	int		i;
	double	tmp;

	if (max == 0)
		return (-1);
	i = 1;
	tmp = res[i];
	while (i < max)
	{
		if (res[i] > 0.0 && res[i] < tmp)
			tmp = res[i];
		i++;
	}
	if (tmp <= 0.0)
		return (-1);
	return (tmp);
}

static double	*fill_p(t_ray *ray, t_object obj, double *pos)
{
	double *p;

	p = new_double(5);
	p[0] = pow(ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y
	+ ray->dir.z * ray->dir.z, 2);
	p[1] = 4 * (ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y
	+ ray->dir.z * ray->dir.z) * (ray->dir.x * pos[0] + ray->dir.y
	* pos[1] + ray->dir.z * pos[2]);
	p[2] = 2 * (ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y
	+ ray->dir.z * ray->dir.z) * (pos[0] * pos[0] + pos[1] * pos[1]
	+ pos[2] * pos[2] + obj.max * obj.max - obj.min * obj.min)
	+ 4 * pow(ray->dir.x * pos[0] + ray->dir.y * pos[1]
	+ ray->dir.z * pos[2], 2) - 4 * obj.max * obj.max
	* (ray->dir.x * ray->dir.x * obj.b.x + ray->dir.y * ray->dir.y * obj.b.y
	+ ray->dir.z * ray->dir.z * obj.b.z);
	p[3] = 4 * (ray->dir.x * pos[0] + ray->dir.y * pos[1]
	+ ray->dir.z * pos[2]) * (pos[0] * pos[0] + pos[1] * pos[1]
	+ pos[2] * pos[2] + obj.max * obj.max - obj.min * obj.min)
	- 8 * obj.max * obj.max * (ray->dir.x * pos[0] * obj.b.x
	+ ray->dir.y * pos[1] * obj.b.y + ray->dir.z * pos[2] * obj.b.z);
	p[4] = pow(pos[0] * pos[0] + pos[1] * pos[1]
	+ pos[2] * pos[2] + obj.max * obj.max - obj.min * obj.min, 2)
	- 4 * obj.max * obj.max * (pos[0] * pos[0] * obj.b.x + pos[1] * pos[1]
	* obj.b.y + pos[2] * pos[2] * obj.b.z);
	return (p);
}

double			check_torus(t_ray *ray, t_object obj)
{
	double *pos;
	double *p;
	double *res;
	double tmp;

	res = new_double(4);
	pos = new_double(3);
	pos[0] = ray->a.x - obj.a.x;
	pos[1] = ray->a.y - obj.a.y;
	pos[2] = ray->a.z - obj.a.z;
	p = fill_p(ray, obj, pos);
	tmp = quartic(p, res);
	tmp = ft_condition(res, tmp);
	free(pos);
	free(p);
	free(res);
	return (tmp);
}

t_v				normal_torus(t_ray *ray, t_object *obj)
{
	t_v		res;
	double	*pos;
	double	r;
	double	a;

	pos = (double*)malloc(sizeof(double) * 3);
	pos[0] = ray->a.x - obj->a.x;
	pos[1] = ray->a.y - obj->a.y;
	pos[2] = ray->a.z - obj->a.z;
	r = obj->max;
	res.x = ray->dir.x * ray->t + pos[0];
	res.y = ray->dir.y * ray->t + pos[1];
	res.z = ray->dir.z * ray->t + pos[2];
	a = 1.0 - (r / sqrt(res.x * res.x + res.y * res.y + res.z * res.z));
	obj->b.x != 0 ? (res.x *= a * obj->b.x) : 0;
	obj->b.y != 0 ? (res.y *= a * obj->b.y) : 0;
	obj->b.z != 0 ? (res.z *= a * obj->b.z) : 0;
	free(pos);
	return (res);
}
