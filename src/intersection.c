/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 10:48:58 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:36:31 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static double	check_intersection(t_ray *ray, t_object obj)
{
	double	res;

	res = -1;
	if (obj.type == 1)
	{
		res = check_sphere(ray, obj);
	}
	else if (obj.type == 2)
		res = check_cylinder(ray, obj);
	else if (obj.type == 3)
		res = check_plane(ray, &obj);
	else if (obj.type == 4)
		res = check_cone(ray, obj);
	else if (obj.type == 5)
		res = check_triangle(ray, &obj);
	else if (obj.type == 6)
		res = check_torus(ray, obj);
	else if (obj.type == 7)
		res = check_ct(ray, obj);
	else if (obj.type == 8)
		res = check_ellipsoid(ray, obj);
	return (res);
}

void			intersection(t_ray *ray, t_object *obj, int nbobj)
{
	double	res;
	int		i;

	i = 0;
	res = -1;
	while (i < nbobj)
	{
		res = check_intersection(ray, obj[i]);
		if (res >= 0 && ray->t != -1 && res < ray->t)
		{
			ray->id = i;
			ray->t = res;
		}
		else if (res >= 0 && ray->t == -1)
		{
			ray->id = i;
			ray->t = res;
		}
		i++;
	}
}
