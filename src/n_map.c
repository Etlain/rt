/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:40:34 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 17:45:39 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

t_v		apply_nmap(t_v v, t_v c)
{
	t_v		n;
	t_v		*vrep;

	vrep = (t_v*)malloc(sizeof(t_v) * 3);
	set_vrep(v, vrep);
	n = add_v(mult_v(vrep[2], 255 - c.z),\
			add_v(mult_v(vrep[1], 127 - c.y),\
			mult_v(vrep[0], c.x - 255)));
	ft_memdel((void**)&vrep);
	return (n);
}
