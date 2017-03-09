/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:52:01 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 15:48:21 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	put_cl_fd(char *str, t_v val, int fd)
{
	ft_putstr_fd("\t", fd);
	ft_putstr_fd(str, fd);
	ft_putdouble_fd(val.x, fd);
	ft_putchar_fd(';', fd);
	ft_putdouble_fd(val.y, fd);
	ft_putchar_fd(';', fd);
	ft_putdouble_fd(val.z, fd);
	ft_putchar_fd('\n', fd);
	ft_putchar('\n');
}

void	put_nb_fd(char *str, double nb, int fd, int i)
{
	ft_putstr_fd(str, fd);
	ft_putdouble_fd(nb, fd);
	ft_putchar_fd('\n', fd);
}
