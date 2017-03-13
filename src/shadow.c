/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:16:39 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 12:47:31 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static double	ft_ret(double n, int nb)
{
	double ret;

	ret = (double)(1 / (double)nb) * n;
	if (nb == 0)
		ret = 0;
	return (ret);
}

static t_v		ft_t(t_ray r, t_object *obj, t_light *l, int i)
{
	t_v		norm1;

	get_normal(&r, &obj[r.id]);
	norm1 = set_v(obj[r.id].c.x, obj[r.id].c.y, obj[r.id].c.z);
	if (obj[r.id].type == 5)
		norm1 = get_normal_other(&r, &obj[r.id], l[i]);
	norm1 = normalize(norm1);
	return (norm1);
}

double			shadow(t_light *l, t_ray ray, t_object *obj, int *nb)
{
	int		i;
	int		n;
	t_ray	r;
	t_v		norm1;
	t_v		norm2;

	i = -1;
	n = 0;
	while (++i < nb[1])
	{
		r.id = -1;
		r.t = -1;
		r.a = l[i].pos;
		r.dir = get_v(r.a, add_v(ray.a, mult_v(ray.dir, ray.t)));
		r.dir = normalize(r.dir);
		intersection(&r, obj, nb[0]);
		r.current = add_v(r.a, mult_v(r.dir, r.t));
		norm1 = ft_t(r, obj, l, i);
		norm2 = ft_t(ray, obj, l, i);
		if (r.id == ray.id && dot(norm1, norm2) > 0.9)
			++n;
	}
	return (ft_ret(n, nb[1]));
}
