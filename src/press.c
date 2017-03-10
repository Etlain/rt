/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:10:02 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 14:27:24 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

int		mouse_button(int key, int x, int y, void *param)
{
	t_winfo	*w;
	t_v		*v;

	w = param;
	v = (t_v*)malloc(sizeof(t_v) * 3);
	v[0] = set_v(0, 0, 0);
	v[1] = set_v(0, 0, 0);
	v[2] = set_v(0, 0, 0);
	key = 0;
	if ((x >= 0 && x < W) && (y >= 0 && y < H))
	{
		set_vrep(w->cam.dir, v);
		w->ray.a = w->cam.pos;
		w->ray.dir = normalize(add_v(add_v(mult_v(v[0], x - W / 2),
		mult_v(v[1], H / 2 - y)), mult_v(v[2], W / 2)));
		w->ray.id = -1;
		w->ray.t = -1;
		intersection(&w->ray, w->obj, w->file.nbobj);
		w->opt.oselect = w->ray.id;
	}
	return (0);
}

int		key_press(int key, void *param)
{
	t_winfo	*w;

	w = param;
	if (w->file.nbobj < 1 && w->opt.oselect != -1)
		w->opt.oselect = -1;
	else if (w->opt.oselect < 0 || w->opt.oselect >= w->file.nbobj)
		w->opt.oselect = -1;
	if (w->file.nblight < 1 && w->opt.lselect != -1)
		w->opt.lselect = -1;
	else if (w->opt.lselect < 0 || w->opt.lselect >= w->file.nblight)
		w->opt.lselect = -1;
	if (key == 53)
		exit(1);
	else if (w->opt.console == 0)
		press_noconsole(w, key);
	else if (w->opt.console == 1)
		press_console(w, key);
	return (0);
}
