/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:28:14 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:36:19 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	get_split(t_v *v, char **file, int x, int y)
{
	char	**split;

	split = ft_strsplit(&file[y][x], ';');
	if (check_split(split, 3) == 1)
	{
		v->x = ft_atod(split[0]);
		v->y = ft_atod(split[1]);
		v->z = ft_atod(split[2]);
		free_memory((void**)split, 3);
	}
}

char	*del_space(char *str, int i)
{
	char	*dst;
	int		end;

	while (str[i] == ' ' && str[i] != '\0')
		i++;
	end = i;
	while (str[end] != ' ' && str[i] != '\0')
		end++;
	dst = ft_strsub(str, i, end - i);
	return (dst);
}
