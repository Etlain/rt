/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:12:48 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 18:31:09 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	get_arg(t_text *text, char **file, int x, int y)
{
	if (ft_strncmp("/texture:", &file[y][x], 9) == 0)
		get_texture(&text->texture, &file[y][x + 10]);
	else if (ft_strncmp("/nmap:", &file[y][x], 6) == 0)
		get_texture(&text->normal, &file[y][x + 7]);
	else if (ft_strncmp("/reflection:", &file[y][x], 12) == 0)
	{
		text->r = ft_atod(&file[y][x + 12]);
		if (text->r < 0)
			text->r = 0;
		else if (text->r > 1)
			text->r = 1;
	}
}

static int	get_text_arg(t_text *text, char **file, int x, int y)
{
	y++;
	ensure_texture(text);
	while (file[y] != NULL)
	{
		x = 0;
		while (file[y][x] != '\0' || (file[y][x] == '.' && x != 0))
		{
			if (file[y][x] == '/')
				get_arg(text, file, x, y);
			x++;
		}
		if (file[y][x] == '.')
			return (0);
		y++;
	}
	return (0);
}

static void	get_text_if2(t_winfo *w, int x, int y, int *index)
{
	if (ft_strcmp(".triangle:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else if (ft_strcmp(".torus:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else if (ft_strcmp(".holecube:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else if (ft_strcmp(".ellipsoid:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
}

static void	get_text_if(t_winfo *w, int x, int y, int *index)
{
	if (ft_strcmp(".sphere:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else if (ft_strcmp(".cylinder:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else if (ft_strcmp(".plane:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else if (ft_strcmp(".cone:", &w->file.file[y][x]) == 0)
	{
		get_text_arg(&w->text[*index], w->file.file, x, y);
		(*index)++;
	}
	else
		get_text_if2(w, x, y, index);
}

void		get_objecttexture(t_winfo *w)
{
	int	index;
	int	x;
	int	y;

	y = 0;
	index = 0;
	w->text = NULL;
	if (w->file.nbobj != 0)
		w->text = (t_text *)malloc(sizeof(t_text) * w->file.nbobj);
	while (y < w->file.size)
	{
		x = 0;
		while (w->file.file[y][x] != '\0')
		{
			get_text_if(w, x, y, &index);
			x++;
		}
		y++;
	}
}
