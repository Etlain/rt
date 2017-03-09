/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:48:30 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 11:37:59 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

double			*new_double(int nbr)
{
	double	*a;
	int		i;

	i = 0;
	a = (double *)malloc(sizeof(double) * nbr);
	while (i < nbr)
	{
		a[i] = 0;
		i++;
	}
	return (a);
}
