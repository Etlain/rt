/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:29:15 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 14:07:14 by aputman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

double	get_t_a(double delta, double a, double b)
{
	double	t1;
	double	t2;

	if (delta == 0)
	{
		t1 = -b / (2 * a);
		return (t1);
	}
	else if (delta > 0)
	{
		t1 = (-b - sqrt(delta)) / (2 * a);
		t2 = (-b + sqrt(delta)) / (2 * a);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	return (-1);
}

double	dpower(double n, double t)
{
	double	ret;
	int		i;

	i = 1;
	ret = n;
	while (i < t)
	{
		ret *= n;
		i++;
	}
	return (ret);
}

t_v		limit_v(t_v v, double min, double max)
{
	if (v.x < min)
		v.x = min;
	else if (v.x > max)
		v.x = max;
	if (v.y < min)
		v.y = min;
	else if (v.y > max)
		v.y = max;
	if (v.z < min)
		v.z = min;
	else if (v.z > max)
		v.z = max;
	return (v);
}

void	set_vrep(t_v d, t_v *v)
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
