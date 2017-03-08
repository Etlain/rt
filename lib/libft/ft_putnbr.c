/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:20:09 by abara             #+#    #+#             */
/*   Updated: 2015/12/08 14:35:21 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long	power;
	long	i;

	i = (long)n;
	power = 1;
	if (i < 0)
	{
		ft_putchar('-');
		i = -i;
	}
	while (power <= i)
		power *= 10;
	if (i > 0)
		power /= 10;
	while (i >= 0 && power != 0)
	{
		ft_putchar((i / power) + 48);
		i %= power;
		power /= 10;
	}
}
