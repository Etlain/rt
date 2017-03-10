/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:12:48 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 15:01:49 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	get_arg(t_object *obj, char **file, int x, int y)
{
	if (ft_strncmp("/pos:", &file[y][x], 5) == 0)
		get_split(&obj->a, file, x + 5, y);
	else if (ft_strncmp("/dir:", &file[y][x], 5) == 0)
		get_split(&obj->b, file, x + 5, y);
	else if (ft_strncmp("/normal:", &file[y][x], 8) == 0)
		get_split(&obj->c, file, x + 8, y);
	else if (ft_strncmp("/color:", &file[y][x], 7) == 0)
		get_split(&obj->color, file, x + 7, y);
	else if (ft_strncmp("/r:", &file[y][x], 3) == 0)
		obj->r = ft_atod(&file[y][x + 3]);
	else if (ft_strncmp("/min:", &file[y][x], 5) == 0)
		obj->min = ft_atod(&file[y][x + 5]);
	else if (ft_strncmp("/max:", &file[y][x], 5) == 0)
		obj->max = ft_atod(&file[y][x + 5]);
	else if (ft_strncmp("/a:", &file[y][x], 3) == 0)
		get_split(&obj->a, file, x + 3, y);
	else if (ft_strncmp("/b:", &file[y][x], 3) == 0)
		get_split(&obj->b, file, x + 3, y);
	else if (ft_strncmp("/c:", &file[y][x], 3) == 0)
		get_split(&obj->c, file, x + 3, y);
}

static int	get_object_arg(t_object *obj, char **file, int x, int y)
{
	y++;
	ensure_object(obj);
	while (file[y] != NULL)
	{
		x = 0;
		while (file[y][x] != '\0' && (file[y][x] != '.' &&
					ft_isdigit(file[y][x + 1]) != 1))
		{
			if (file[y][x] == '/')
				get_arg(obj, file, x, y);
			x++;
		}
		if (file[y][x] == '.')
			return (0);
		y++;
	}
	return (0);
}

static void	get_obj(t_winfo *w, t_xy xy, int *index, int type)
{
	w->obj[*index].type = type;
	get_object_arg(&w->obj[*index], w->file.file, xy.x, xy.y);
	(*index)++;
}

static void	get_object_if(t_winfo *w, int x, int y, int *index)
{
	t_xy xy;

	xy.x = x;
	xy.y = y;
	if (ft_strcmp(".sphere:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 1);
	else if (ft_strcmp(".cylinder:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 2);
	else if (ft_strcmp(".plane:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 3);
	else if (ft_strcmp(".cone:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 4);
	else if (ft_strcmp(".triangle:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 5);
	else if (ft_strcmp(".torus:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 6);
	else if (ft_strcmp(".holecube:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 7);
	else if (ft_strcmp(".ellipsoid:", &w->file.file[y][x]) == 0)
		get_obj(w, xy, index, 8);
}

void		get_object(t_winfo *w)
{
	int	index;
	int	x;
	int	y;

	y = 0;
	index = 0;
	w->obj = NULL;
	if (w->file.nbobj != 0)
		w->obj = (t_object *)malloc(sizeof(t_object) * w->file.nbobj);
	while (y < w->file.size)
	{
		x = 0;
		while (w->file.file[y][x] != '\0')
		{
			get_object_if(w, x, y, &index);
			x++;
		}
		y++;
	}
}
