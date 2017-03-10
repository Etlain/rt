/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cguilbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 14:30:34 by cguilbar          #+#    #+#             */
/*   Updated: 2017/02/13 11:08:34 by cguilbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RT.h"

void		set_vrep(cl_float3 d, cl_float3 v[3])
{
	v[2] = d;
	normalize(&v[2]);
	if (fabs(v[2].y) == 1)
	{
		v[0].x = 1;
		v[1].z = -v[2].y;
		return ;
	}
	v[0].x = v[2].z;
	v[0].z = -v[2].x;
	v[1].y = sqrt(v[2].x * v[2].x + v[2].z * v[2].z);
	v[1].x = -v[2].x / (fabs(v[2].x) + fabs(v[2].z)) * v[2].y;
	v[1].z = -v[2].z / (fabs(v[2].x) + fabs(v[2].z)) * v[2].y;
}

cl_float3		apply_nmap(cl_float3 v, cl_float3 c)
{
	cl_float3	vrep[3];

	set_vrep(v, vrep);
	return (add_vec3(mult_vec3(vrep[2], 255 - c.z),\
			add_vec3(mult_vec3(vrep[1], 127 - c.y),\
			mult_vec3(vrep[0], c.x - 255))));
}
