/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ensure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:44:56 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 15:37:51 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	ensure_object(t_object *obj)
{
	obj->a = set_v(0, 0, 0);
	obj->b = set_v(0, 1, 0);
	if (obj->type == 6)
		obj->b = set_v(1, 1, 0);
	else if (obj->type == 8)
		obj->b = set_v(4, 2, 1);
	obj->c = set_v(-1, 0, 0);
	obj->color = set_v(255, 255, 255);
	obj->r = 5;
	if (obj->type == 4)
		obj->r = 30;
	obj->min = 5;
	obj->max = 5;
}

void	ensure_texture(t_text *text)
{
	text->texture.texture = NULL;
	text->normal.texture = NULL;
	text->r = 0;
	text->d = 0;
}

void	ensure_light(t_light *light)
{
	light->pos = set_v(0, 0, 0);
	light->color = set_v(255, 255, 255);
}
