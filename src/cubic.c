/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 16:41:47 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 11:31:46 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static double	fill_pq_delta(double *pq, double *pol)
{
	double delta;

	pq[0] = (pol[2] / pol[0]) - ((pol[1] * pol[1]) / (3.0 * pol[0] * pol[0]));
	pq[1] = ((2.0 * pol[1] * pol[1] * pol[1])
	/ (27.0 * pol[0] * pol[0] * pol[0]))
	+ (pol[3] / pol[0]) - ((pol[1] * pol[2])
	/ (3.0 * pol[0] * pol[0]));
	delta = pq[1] * pq[1] + ((4.0 * pq[0] * pq[0] * pq[0]) / 27.0);
	return (delta);
}

static int		res_neg(double *res, double *pq, double *pol)
{
	double k;

	k = 0;
	while ((int)k < 3)
	{
		res[(int)k] = (2.0 * sqrt(-pq[0] / 3.0) * cos((1.0 / 3.0) *
		acos((-pq[1] / 2.0) * sqrt(27.0 / (-pq[0] * pq[0] * pq[0])))
		+ (2.0 * k * M_PI) / 3.0)) - pol[1] / (3.0 * pol[0]);
		k++;
	}
	return (3);
}

static int		res_eq(double *res, double *pq, double *pol)
{
	res[0] = ((3.0 * pq[1]) / pq[0]) - (pol[1] / (3.0 * pol[0]));
	res[1] = -(3.0 * pq[1]) / pq[0] - pol[1] / (3.0 * pol[0]);
	return (2);
}

int				cubic(double *pol, double *res)
{
	double	delta;
	double	*pq;
	double	u;
	double	v;
	int		sol;

	sol = 0;
	if (pol[0] == 0)
		return (degree_2(&pol[1], res));
	pq = new_double(2);
	delta = fill_pq_delta(pq, pol);
	if (delta > 0)
	{
		u = cbrt((-pq[1] + sqrt(delta)) / 2.0);
		v = cbrt((-pq[1] - sqrt(delta)) / 2.0);
		res[0] = u + v - pol[1] / (3 * pol[0]);
		sol = 1;
	}
	else if (delta == 0)
		sol = res_eq(res, pq, pol);
	else if (delta < 0)
		sol = res_neg(res, pq, pol);
	free(pq);
	return (sol);
}
