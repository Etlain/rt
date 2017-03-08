/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:07:55 by abara             #+#    #+#             */
/*   Updated: 2015/12/08 15:13:06 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size(long n)
{
	if (n < 0)
		return (ft_size(-n) + 1);
	if (n < 10)
		return (1);
	return (ft_size(n / 10) + 1);
}

static char		*ft_tabin(char *tab, long n, long power, int i)
{
	while (n >= 0 && power != 0)
	{
		tab[i] = (n / power) + 48;
		n %= power;
		power /= 10;
		i++;
	}
	return (tab);
}

char			*ft_itoa(int n)
{
	char	*tab;
	long	power;
	int		i;
	int		index;
	long	k;

	k = (long)n;
	index = ft_size(k);
	i = 0;
	power = 1;
	tab = malloc(sizeof(*tab) * index + 1);
	if (tab == NULL)
		return (NULL);
	if (k < 0)
	{
		tab[i] = '-';
		k = -k;
		i++;
	}
	while (power <= k)
		power *= 10;
	k > 0 ? power /= 10 : 0;
	tab = ft_tabin(tab, k, power, i);
	tab[index] = '\0';
	return (tab);
}
