/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 13:00:54 by abara             #+#    #+#             */
/*   Updated: 2017/02/24 13:02:20 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int n, int t)
{
	int	ret;
	int	i;

	i = 1;
	ret = n;
	while (i < t)
	{
		ret *= n;
		i++;
	}
	return (ret);
}
