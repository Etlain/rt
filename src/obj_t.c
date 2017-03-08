/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 10:53:49 by cguilbar          #+#    #+#             */
/*   Updated: 2017/03/08 17:07:26 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

t_v	plane_t(t_object *obj, t_texture *text, t_v p)
{
	double	x;
	double	y;
	t_v		vrep[3];
	t_v		color;
	unsigned int	i;

//	ft_putendl("Enter");
	set_vrep(obj->c, vrep);
	p = get_v(obj->a, p);
	x = fmod(dot(p, vrep[0]), 10) / 10;
	y = fmod(dot(p, vrep[1]), 10) / 10;
	if (x < 0)
		x += 1;
	if (y < 0)
		y += 1;
//	printf("(%f, %f)\n", x, y);
	i = (unsigned int)(x * text->w * 3) + (unsigned int)(y * text->h * 3) * text->w * 3;
//	printf("I: %d || MAX: %d\n", i, text->h * text->w * 3);
//	ft_putendl("Check");
	color.x = text->texture[i];
	color.y = text->texture[i + 1];
	color.z = text->texture[i + 2];
//	ft_putendl("Out");
	return (color);
}

t_v	sphere_t(t_object *obj, t_texture *text, t_v p)
{
	double	x;
	double	y;
	t_v		vrep[3];
	t_v		color;
	int		i;

	obj->b = set_v(1, 0, 0);
	set_vrep(obj->b, vrep);
	p = normalize(get_v(obj->a, p));
	x = (dot(p, vrep[0]) + 1) / 2;
	y = (dot(p, vrep[1]) + 1) / 2;
	i = (int)(x * text->w * 3) + (int)(y * text->h * 3) * text->w * 3;
	color.x = text->texture[i];
	color.y = text->texture[i + 1];
	color.z = text->texture[i + 2];
	return (color);
}

t_v	cylinder_t(t_object *obj, t_texture *text, t_v p)
{
	double	x;
	double	y;
	t_v		vrep[3];
	t_v		color;
	int		i;

	set_vrep(obj->b, vrep);
	p = normalize(get_v(obj->a, p));
	x = (dot(p, vrep[0]) + 1) / 2;
	y = fmod(dot(p, vrep[2]), 1);
	i = (int)(x * text->w * 3) + (int)(y * text->h * 3) * text->w * 3;
	color.x = text->texture[i];
	color.y = text->texture[i + 1];
	color.z = text->texture[i + 2];
	return (color);
}
