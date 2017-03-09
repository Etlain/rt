/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 16:22:45 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 12:54:04 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static int		copy_struct(t_winfo *winfo, t_object *o, t_text *text)
{
	int	i;
	int	max;

	max = winfo->file.nbobj - 1;
	i = 0;
	while (i < max)
	{
		o[i] = winfo->obj[i];
		text[i] = winfo->text[i];
		i++;
	}
	return (i);
}

static void		create_object_by_id(t_winfo *winfo, char *cmd, int id)
{
	t_text		*text;
	t_object	*o;
	t_object	*er;
	int			i;

	winfo->file.nbobj++;
	o = (t_object*)malloc(sizeof(t_object) * i);
	text = (t_text*)malloc(sizeof(t_text) * i);
	i = copy_struct(winfo, o, text);
	o[i].type = id;
	ensure_object(&o[i]);
	ensure_texture(&text[i]);
	o[i].color = set_v(165, 65, 125);
	o[i].a = add_v(winfo->cam.pos, mult_v(normalize(winfo->cam.dir), 20));
	if (ft_strncmp(" ", cmd, 1) == 0)
		get_nbr(&o[i].a, cmd);
	er = winfo->obj;
	winfo->obj = o;
	free(er);
	free(winfo->text);
	winfo->text = text;
}

static void		create_light(t_winfo *winfo, char *cmd)
{
	t_light *o;
	t_light *er;
	int		i;
	int		max;

	winfo->file.nblight++;
	i = winfo->file.nblight;
	o = (t_light*)malloc(sizeof(t_light) * i);
	max = i - 1;
	i = 0;
	while (i < max)
	{
		o[i] = winfo->light[i];
		i++;
	}
	ensure_light(&o[i]);
	o[i].pos = add_v(winfo->cam.pos, mult_v(normalize(winfo->cam.dir), 20));
	if (ft_strncmp(" ", cmd, 1) == 0)
		get_nbr(&o[i].pos, cmd);
	er = winfo->light;
	winfo->light = o;
	free(er);
}

static void		create_object(t_winfo *winfo, char *cmd)
{
	if (ft_strncmp("sphere", cmd, 6) == 0)
		create_object_by_id(winfo, &cmd[6], 1);
	else if (ft_strncmp("cylinder", cmd, 8) == 0)
		create_object_by_id(winfo, &cmd[9], 2);
	else if (ft_strncmp("plane", cmd, 5) == 0)
		create_object_by_id(winfo, &cmd[6], 3);
	else if (ft_strncmp("cone", cmd, 4) == 0)
		create_object_by_id(winfo, &cmd[5], 4);
	else if (ft_strncmp("triangle", cmd, 8) == 0)
		create_object_by_id(winfo, &cmd[9], 5);
	else if (ft_strncmp("torus", cmd, 5) == 0)
		create_object_by_id(winfo, &cmd[6], 6);
	else if (ft_strncmp("holecube", cmd, 8) == 0)
		create_object_by_id(winfo, &cmd[9], 7);
	else if (ft_strncmp("ellipsoid", cmd, 9) == 0)
		create_object_by_id(winfo, &cmd[10], 8);
	else if (ft_strncmp("light", cmd, 5) == 0)
		create_light(winfo, &cmd[5]);
}

void			ft_create(t_winfo *winfo, char *cmd)
{
	char *elem;

	elem = ft_strtrim(&cmd[7]);
	create_object(winfo, elem);
	free(elem);
}
