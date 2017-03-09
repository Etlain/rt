/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degree_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:47:35 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 11:31:59 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

int				degree_2(double *pol, double *res)
{
	double delta;

	delta = pol[1] * pol[1] - 4 * pol[0] * pol[2];
	if (delta == 0)
	{
		res[0] = -pol[1] / (2 * pol[0]);
		return (1);
	}
	else if (delta > 0)
	{
		res[0] = (-pol[1] + sqrt(delta)) / (2 * pol[0]);
		res[1] = (-pol[1] - sqrt(delta)) / (2 * pol[0]);
		return (2);
	}
	else
		return (0);
}
