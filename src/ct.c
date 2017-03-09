/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ct.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:37:13 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 12:00:47 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static double	*fill_p(t_ray *ray, t_object obj, double *pos)
{
	double *p;

	p = (double*)malloc(sizeof(double) * 5);
	p[0] = pow(ray->dir.x, 4) + pow(ray->dir.y, 4) + pow(ray->dir.z, 4);
	p[1] = 4 * (pow(ray->dir.x, 3) * pos[0] + pow(ray->dir.y, 3) * pos[1]
	+ pow(ray->dir.z, 3) * pos[2]);
	p[2] = 6 * (pow(ray->dir.x, 2) * pow(pos[0], 2) + pow(ray->dir.y, 2)
	* pow(pos[1], 2) + pow(ray->dir.z, 2) * pow(pos[2], 2))
	- 5 * (pow(ray->dir.x, 2) + pow(ray->dir.y, 2) + pow(ray->dir.z, 2));
	p[3] = 4 * (pow(pos[0], 3) * ray->dir.x + pow(pos[1], 3) * ray->dir.y
	+ pow(pos[2], 3) * ray->dir.z)
	- 10 * (ray->dir.x * pos[0] + ray->dir.y * pos[1] + ray->dir.z * pos[2]);
	p[4] = pow(pos[0], 4) + pow(pos[1], 4) + pow(pos[2], 4)
	- 5 * (pow(pos[0], 2) + pow(pos[1], 2) + pow(pos[2], 2)) + obj.r;
	return (p);
}

double			check_ct(t_ray *ray, t_object obj)
{
	double	*p;
	double	*pos;
	double	*res;
	int		sol;
	double	tmp;

	res = (double*)malloc(sizeof(double) * 4);
	pos = (double*)malloc(sizeof(double) * 3);
	pos[0] = ray->a.x - obj.a.x;
	pos[1] = ray->a.y - obj.a.y;
	pos[2] = ray->a.z - obj.a.z;
	p = fill_p(ray, obj, pos);
	sol = quartic(p, res);
	tmp = ft_condition(res, sol);
	free(res);
	free(p);
	free(pos);
	return (tmp);
}

t_v				normal_ct(t_ray *ray, t_object *obj)
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
	res.x = 4 * pow(res.x, 3) - 10 * res.x;
	res.y = 4 * pow(res.y, 3) - 10 * res.y;
	res.z = 4 * pow(res.z, 3) - 10 * res.z;
	free(pos);
	return (res);
}
