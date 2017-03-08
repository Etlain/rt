/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:20:09 by abara             #+#    #+#             */
/*   Updated: 2015/12/08 14:37:42 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	power;
	long	i;

	i = (long)n;
	power = 1;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = -i;
	}
	while (power <= i)
		power *= 10;
	if (i > 0)
		power /= 10;
	while (i >= 0 && power != 0)
	{
		ft_putchar_fd((i / power) + 48, fd);
		i %= power;
		power /= 10;
	}
}
