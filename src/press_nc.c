/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_nc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputman <aputman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 14:05:44 by aputman           #+#    #+#             */
/*   Updated: 2017/03/13 15:02:02 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static t_v	rot_v(int key, t_v v)
{
	t_v		vrep[3];

	set_vrep(v, vrep);
	if (key == 126)
		v = add_v(vrep[2], mult_v(vrep[1], -0.5));
	else if (key == 125)
		v = add_v(vrep[2], mult_v(vrep[1], 0.5));
	else if (key == 123)
		v = add_v(vrep[2], mult_v(vrep[0], -0.5));
	else if (key == 124)
		v = add_v(vrep[2], mult_v(vrep[0], 0.5));
	return (normalize(v));
}

static void	press_l(t_winfo *w, int key)
{
	t_v		vrep[3];

	set_vrep(w->cam.dir, vrep);
	if (key == 13)
		w->light[(int)w->opt.lselect].pos =
			add_v(w->light[(int)w->opt.lselect].pos, mult_v(vrep[2],
						w->opt.speed));
	else if (key == 1)
		w->light[w->opt.lselect].pos =
			add_v(w->light[w->opt.lselect].pos, mult_v(vrep[2], -w->opt.speed));
	else if (key == 0)
		w->light[w->opt.lselect].pos =
			add_v(w->light[w->opt.lselect].pos, mult_v(vrep[0], -w->opt.speed));
	else if (key == 2)
		w->light[w->opt.lselect].pos =
			add_v(w->light[w->opt.lselect].pos, mult_v(vrep[0], w->opt.speed));
	else if (key == 15)
		w->light[w->opt.lselect].pos =
			add_v(w->light[w->opt.lselect].pos, mult_v(vrep[1], w->opt.speed));
	else if (key == 3)
		w->light[w->opt.lselect].pos =
			add_v(w->light[w->opt.lselect].pos, mult_v(vrep[1], -w->opt.speed));
}

static t_v	trans_p(t_winfo *w, int key, t_v p)
{
	t_v		vrep[3];

	set_vrep(w->cam.dir, vrep);
	if (key == 126)
		p = add_v(p, mult_v(vrep[2], w->opt.speed));
	else if (key == 125)
		p = add_v(p, mult_v(vrep[2], -w->opt.speed));
	else if (key == 123)
		p = add_v(p, mult_v(vrep[0], -w->opt.speed));
	else if (key == 124)
		p = add_v(p, mult_v(vrep[0], w->opt.speed));
	else if (key == 86)
		p = add_v(p, mult_v(vrep[1], w->opt.speed));
	else if (key == 83)
		p = add_v(p, mult_v(vrep[1], -w->opt.speed));
	return (p);
}

static void	other_key(t_winfo *w, int key)
{
	if (key == 269)
		w->opt.trt = !w->opt.trt;
	else if (key == 18)
		w->opt.oselect = -1;
	else
	{
		if (key == 69 && w->opt.oselect != -1)
			w->text[w->ray.id].d += 0.01;
		else if (key == 78 && w->opt.oselect != -1)
			w->text[w->ray.id].d -= 0.01;
		if (w->opt.render == 0)
			render_cpu(w);
		else
			render_gpu(w);
	}
}

void		press_noconsole(t_winfo *w, int key)
{
	if (w->opt.oselect == -1)
	{
		if (!w->opt.trt)
			w->cam.pos = trans_p(w, key, w->cam.pos);
		else
			w->cam.dir = rot_v(key, w->cam.dir);
	}
	else
	{
		if (!w->opt.trt)
			w->obj[w->opt.oselect].a = trans_p(w, key,
					w->obj[w->opt.oselect].a);
		else
			w->obj[w->opt.oselect].b = rot_v(key, w->obj[w->opt.oselect].b);
	}
	if (w->opt.lselect != -1)
		press_l(w, key);
	if (key == 50)
	{
		w->opt.console = 1;
		draw_console(w, w->opt.color);
		mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
	}
	else
		other_key(w, key);
}
