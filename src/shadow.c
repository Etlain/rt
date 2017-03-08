/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 13:16:39 by abara             #+#    #+#             */
/*   Updated: 2017/03/08 13:13:46 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

double	shadow(t_light *l, t_ray ray, t_object *obj, int *nb)
{
	double	ret;
	int		i;
	int		n;
	t_ray	r;
	t_v		v;
	double	d;
	double	a;
	double	b;
	t_v		norm1;
	t_v		norm2;

	i = 0;
	n = 0;
	while (i < nb[1])
	{
		r.id = -1;
		r.t = -1;
		r.a = l[i].pos;
		r.dir = get_v(r.a, add_v(ray.a, mult_v(ray.dir, ray.t)));
		r.dir = normalize(r.dir);
		intersection(&r, obj, nb[0]);
		r.current = add_v(r.a, mult_v(r.dir, r.t));
		get_normal(&r, &obj[r.id]);
		norm1 = set_v(obj[r.id].c.x, obj[r.id].c.y, obj[r.id].c.z);
		if (obj[r.id].type == 5)
			norm1 = get_normal_other(&r, &obj[r.id], l[i]);
		norm1 = normalize(norm1);

		get_normal(&ray, &obj[ray.id]);
		norm2 = set_v(obj[ray.id].c.x, obj[ray.id].c.y, obj[ray.id].c.z);
		if (obj[ray.id].type == 5)
			norm2 = get_normal_other(&ray, &obj[ray.id], l[i]);
		norm2 = normalize(norm2);


/*		v = normalize(get_v(l[i].pos, r.current));
		d = dot(normalize(get_v(ray.a, r.current)), v);
		if (r.id == ray.id && d >= 0)
			n++;
		else if (r.id == ray.id && obj[ray.id].type == 3)
			n++;*/
		if (r.id == ray.id && dot(norm1, norm2) > 0.9)
		{
		//	printf("DOT PRODUCT: %f\n", dot(norm1, norm2));
			n++;
		}
		i++;
	}
	ret = (double)(1 / (double)nb[1]) * n;
	if (nb[1] == 0)
		ret = 0;
	return (ret);
}
