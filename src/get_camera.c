/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:56:02 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 14:27:34 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	get_arg(t_winfo *w, char **file, int x, int y)
{
	if (ft_strncmp("/pos:", &file[y][x], 5) == 0)
		get_split(&w->cam.pos, file, x + 5, y);
	else if (ft_strncmp("/dir:", &file[y][x], 5) == 0)
		get_split(&w->cam.dir, file, x + 5, y);
	else if (ft_strncmp("/ref:", &file[y][x], 5) == 0)
		w->opt.ref = ft_atoi(&file[y][x + 5]);
	else if (ft_strncmp("/ambient:", &file[y][x], 9) == 0)
	{
		w->opt.ambient = ft_atod(&file[y][x + 9]);
		if (w->opt.ambient < 0 || w->opt.ambient > 1)
			w->opt.ambient = 0;
	}
	else if (ft_strncmp("/cellshading:", &file[y][x], 13) == 0)
		w->opt.cshade = ft_atoi(&file[y][x + 13]);
}

static int	get_camera_arg(t_winfo *w, char **file, int x, int y)
{
	y++;
	while (file[y] != NULL)
	{
		x = 0;
		while (file[y][x] != '\0' && (file[y][x] != '.'
					&& ft_isdigit(file[y][x + 1]) != 1))
		{
			if (file[y][x] == '/')
				get_arg(w, file, x, y);
			x++;
		}
		if (file[y][x] == '.')
			return (0);
		y++;
	}
	return (0);
}

int			get_camera(t_winfo *w)
{
	int	x;
	int	y;

	y = 0;
	while (y < w->file.size)
	{
		x = 0;
		while (w->file.file[y][x] != '\0')
		{
			if (ft_strcmp(".camera:", &w->file.file[y][x]) == 0)
			{
				get_camera_arg(w, w->file.file, x, y);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (0);
}
