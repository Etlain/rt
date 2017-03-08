/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 14:36:08 by abara             #+#    #+#             */
/*   Updated: 2017/01/11 14:54:45 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

int		check_split(char **split, int nb)
{
	int	index;

	index = 0;
	while (split[index] != NULL)
		index++;
	if (index == nb)
		return (1);
	return (0);
}

void	free_memory(void **mem, int nb)
{
	int	i;

	i = 0;
	if (mem)
	{
		while (i < nb)
		{
			ft_memdel((void**)&mem[i]);
			i++;
		}
		ft_memdel((void**)&mem);
	}
}
