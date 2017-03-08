/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 10:37:38 by abara             #+#    #+#             */
/*   Updated: 2017/03/08 13:14:11 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

t_v reflection(t_ray ray, t_winfo *w, int *nb, int depth)
{
	t_ray	ref;
	t_v		n;
	double	ret;

	if (depth <= 0 || w->text[ray.id].r == 0)
		return (ray.color);
	ref.a = ray.current;
	n = w->obj[ray.id].c;
	ref.dir = add_v(get_v(ray.a, ray.current), mult_v(mult_v(n, 2),
	dot(invert_v(n), get_v(ray.a, ray.current))));
	ref.dir = normalize(ref.dir);
	ref.id = -1;
	ref.t = -1;
	intersection(&ref, w->obj, w->file.nbobj);
	if (ref.id != -1)
	{
		check_light(w->light, &ref, &w->obj[ref.id], nb[1]);
		ret = shadow(w->light, ref, w->obj, nb);
	}
	ref.current = add_v(ref.a, mult_v(ref.dir, ref.t));
	if (ref.id != -1)
		ref.color = mult_v(add_v(mult_v(ray.color, 1 - w->text[ray.id].r), mult_v(limit_v(mult_v(ref.color, ret), 0, 255), 1 - w->text[ref.id].r)), 0.5);
	if (ref.id != -1)
		return (reflection(ref, w, nb, depth - 1));
//	return (set_v(0, 0, 0));
//	return (mult_v(add_v(ray.color, set_v(0, 0, 0)), 0.5));
	return (mult_v(add_v(set_v(0, 0, 0), mult_v(ray.color, 1 - w->text[ray.id].r)), 0.5));
}
