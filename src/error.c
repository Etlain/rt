/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:09:43 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:33:09 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	print_error(int n)
{
	if (n == 0)
		ft_putendl("An error occured (memory allocation).");
	else if (n == 1)
		ft_putendl("File name must end with [.log].");
	else if (n == 2)
		ft_putendl("Can't open this file.");
	else if (n == 3)
		ft_putendl("File is empty.");
	else if (n == 4)
		ft_putendl("There are too much camera, only one accepted.");
	else if (n == 5)
		ft_putendl("A problem occured with the file size.");
	else if (n == 6)
		ft_putendl("Missing filename to open or to create.");
	exit(1);
}
