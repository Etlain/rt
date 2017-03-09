/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:09:37 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:31:20 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static int	get_type_id(t_file *file, char **tab, int x, int y)
{
	if (ft_strcmp(".camera:", &tab[y][x]) == 0)
		file->nbcam += 1;
	else if (ft_strcmp(".light:", &tab[y][x]) == 0)
		file->nblight += 1;
	else if (ft_strcmp(".sphere:", &tab[y][x]) == 0)
		file->nbsphere += 1;
	else if (ft_strcmp(".cylinder:", &tab[y][x]) == 0)
		file->nbcylinder += 1;
	else if (ft_strcmp(".plane:", &tab[y][x]) == 0)
		file->nbplane += 1;
	else if (ft_strcmp(".cone:", &tab[y][x]) == 0)
		file->nbcone += 1;
	else if (ft_strcmp(".triangle:", &tab[y][x]) == 0)
		file->nbtriangle += 1;
	else if (ft_strcmp(".torus:", &tab[y][x]) == 0)
		file->nbtorus += 1;
	else if (ft_strcmp(".holecube:", &tab[y][x]) == 0)
		file->nbct += 1;
	else if (ft_strcmp(".ellipsoid:", &tab[y][x]) == 0)
		file->nbelli += 1;
	if (file->nbcam > 1)
		return (4);
	return (0);
}

static int	check_content(t_file *file, char **tab)
{
	int	check;
	int	x;
	int	y;

	y = 0;
	check = 0;
	while (y < file->size)
	{
		x = 0;
		while (tab[y][x] != '\0')
		{
			if (tab[y][x] == '.')
			{
				if ((check = get_type_id(file, tab, x, y)) != 0)
					return (check);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void		check_file(t_file *file)
{
	int	check;

	if (file->file == NULL)
		print_error(3);
	if ((check = check_content(file, file->file)) != 0)
		print_error(check);
	file->nbobj = file->nbsphere + file->nbcylinder + file->nbelli +
	file->nbplane + file->nbcone + file->nbtriangle + file->nbtorus
	+ file->nbct;
}
