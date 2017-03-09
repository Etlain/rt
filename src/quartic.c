/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quartic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:18:21 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 11:42:01 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void		set_cubic(double *pqr, double *pol, double *p1)
{
	pqr[0] = (-3.0 * pol[1] * pol[1]) / (8.0 * pol[0] * pol[0])
	+ pol[2] / pol[0];
	pqr[1] = ((pol[1] * pol[1] * pol[1]) / 8.0) / (pol[0] * pol[0] * pol[0])
	- ((pol[1] * pol[2]) / 2.0) / (pol[0] * pol[0]) + pol[3] / pol[0];
	pqr[2] = -3.0 * pow((pol[1] / 4.0) / pol[0], 4.0)
	+ ((pol[2] * (pol[1] / 4.0) * (pol[1]) / 4.0)) / (pol[0] * pol[0] * pol[0])
	- ((pol[1] * pol[3]) / 4.0) / (pol[0] * pol[0])
	+ pol[4] / pol[0];
	p1[0] = 8.0;
	p1[1] = -4.0 * pqr[0];
	p1[2] = -8.0 * pqr[2];
	p1[3] = 4.0 * pqr[2] * pqr[0] - pqr[1] * pqr[1];
}

static int		set_res(double *pqr, double *p1, double *res)
{
	double	y;
	double	a0;
	double	b0;
	int		sol;

	y = res[0];
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	res[3] = 0;
	a0 = sqrt(-pqr[0] + 2.0 * y);
	if (2 * y - pqr[0] != 0)
		b0 = -pqr[1] / (2.0 * a0);
	else
		b0 = sqrt(y * y - pqr[2]);
	p1[0] = 1.0;
	p1[1] = -a0;
	p1[2] = y - b0;
	sol = degree_2(p1, res);
	p1[0] = 1.0;
	p1[1] = a0;
	p1[2] = y + b0;
	sol += degree_2(p1, &res[sol]);
	return (sol);
}

int				quartic(double *pol, double *res)
{
	double	*p1;
	double	*pqr;
	int		sol;
	int		i;

	if (pol[0] == 0)
		return (cubic(&pol[1], res));
	pqr = new_double(3);
	p1 = new_double(4);
	set_cubic(pqr, pol, p1);
	cubic(p1, res);
	sol = set_res(pqr, p1, res);
	free(pqr);
	free(p1);
	if (sol == 0)
		return (0);
	i = 0;
	while (i < sol)
	{
		res[i] = res[i] - pol[1] / (4.0 * pol[0]);
		i++;
	}
	return (sol);
}
