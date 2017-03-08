/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:38:07 by abara             #+#    #+#             */
/*   Updated: 2015/12/11 16:47:04 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(char *str)
{
	int		result;
	int		flag;

	result = 0;
	flag = 0;
	if (*str == '\200')
		return (0);
	while (*str == ' ' || ft_isprint(*str) == 0)
		str++;
	if (*str == '-')
	{
		str++;
		flag = 1;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	if (flag == 1)
		return (result * -1);
	return (result);
}
