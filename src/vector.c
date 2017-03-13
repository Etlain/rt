/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:46:19 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 13:32:10 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

t_v		set_v(double x, double y, double z)
{
	t_v v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

double	norm_v(t_v v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_v		normalize(t_v v)
{
	double	len;

	len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	v.x = v.x / len;
	v.y = v.y / len;
	v.z = v.z / len;
	return (v);
}

t_v		get_v(t_v a, t_v b)
{
	t_v	res;

	res.x = b.x - a.x;
	res.y = b.y - a.y;
	res.z = b.z - a.z;
	return (res);
}

t_v		v_mult_v(t_v a, t_v b)
{
	a.x = a.x * b.x;
	a.y = a.y * b.y;
	a.z = a.z * b.z;
	return (a);
}
