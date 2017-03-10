/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 12:29:46 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/10 12:29:53 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	save_other(t_winfo *winfo, int fd, int i)
{
	if (winfo->obj[i].type != 5)
		put_cl_fd("/pos: ", winfo->obj[i].a, fd);
	else
		put_cl_fd("/a: ", winfo->obj[i].a, fd);
	put_cl_fd("/color: ", winfo->obj[i].color, fd);
	put_nb_fd("\t/reflection: ", winfo->text[i].r, fd, i);
	if (winfo->text[i].texture.texture != NULL)
	{
		ft_putstr_fd("\t/texture: ", fd);
		ft_putstr_fd(winfo->text[i].texture.name, fd);
		ft_putchar_fd('\n', fd);
	}
	if (winfo->text[i].normal.texture != NULL)
	{
		ft_putstr_fd("\t/nmap: ", fd);
		ft_putstr_fd(winfo->text[i].normal.name, fd);
		ft_putchar_fd('\n', fd);
	}
	ft_putstr_fd("}\n\n", fd);
}
