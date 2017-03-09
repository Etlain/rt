/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:24:11 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 14:04:06 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	get_arg(t_light *light, char **file, int x, int y)
{
	if (ft_strncmp("/pos:", &file[y][x], 5) == 0)
		get_split(&light->pos, file, x + 5, y);
	else if (ft_strncmp("/color:", &file[y][x], 7) == 0)
		get_split(&light->color, file, x + 7, y);
}

static int	get_light_arg(t_light *light, char **file, int x, int y)
{
	y++;
	ensure_light(light);
	while (file[y] != NULL)
	{
		x = 0;
		while (file[y][x] != '\0' && (file[y][x] != '.' &&
					ft_isdigit(file[y][x + 1]) != 1))
		{
			if (file[y][x] == '/')
				get_arg(light, file, x, y);
			x++;
		}
		if (file[y][x] == '.')
			return (0);
		y++;
	}
	return (0);
}

void		get_light(t_winfo *w)
{
	int	index;
	int	x;
	int	y;

	y = 0;
	index = 0;
	w->light = NULL;
	w->light = (t_light *)malloc(sizeof(t_light) * w->file.nblight);
	while (y < w->file.size)
	{
		x = 0;
		while (w->file.file[y][x] != '\0')
		{
			if (ft_strcmp(".light:", &w->file.file[y][x]) == 0)
			{
				get_light_arg(&w->light[index], w->file.file, x, y);
				index++;
			}
			x++;
		}
		y++;
	}
}
