/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:52:01 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:33:30 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	put_cl_fd(char *str, t_v val, int fd)
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

void		save_file(char *name, t_winfo *winfo)
{
	int	fd;
	int	i;

	fd = open(name, O_RDWR | O_CREAT, 0644);
	ft_putstr_fd(".camera:\n{\n", fd);
	put_cl_fd("/pos: ", winfo->cam.pos, fd);
	put_cl_fd("/dir: ", winfo->cam.dir, fd);
	ft_putstr_fd("\t/ref: ", fd);
	ft_putstr_fd(ft_itoa(winfo->opt.ref), fd);
	ft_putstr_fd("\n}\n\n", fd);
	i = 0;
	while (i < winfo->file.nblight)
	{
		ft_putstr_fd(".light:\n{\n", fd);
		put_cl_fd("/pos: ", winfo->light[i].pos, fd);
		put_cl_fd("/color: ", winfo->light[i].color, fd);
		ft_putstr_fd("}\n\n", fd);

		i++;
	}
	i = 0;
	while (i < winfo->file.nbobj)
	{
		if (winfo->obj[i].type == 1)
		{
			ft_putstr_fd(".sphere:\n{\n", fd);
			ft_putstr_fd("\t/r: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (winfo->obj[i].type == 2)
		{
			ft_putstr_fd(".cylinder:\n{\n", fd);
			ft_putstr_fd("\t/r: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
			put_cl_fd("/dir: ", winfo->obj[i].b, fd);
			ft_putstr_fd("\t/max: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
			ft_putstr_fd("\t/min: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
		}
		else if(winfo->obj[i].type == 3)
		{
			ft_putstr_fd(".plane:\n{\n", fd);
			put_cl_fd("/normal: ", winfo->obj[i].c, fd);
		}
		else if (winfo->obj[i].type == 4)
		{
			ft_putstr_fd(".cone:\n{\n", fd);
			ft_putstr_fd("\t/r: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
			put_cl_fd("/dir: ", winfo->obj[i].b, fd);
			ft_putstr_fd("\t/max: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
			ft_putstr_fd("\t/min: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (winfo->obj[i].type == 5)
		{
			ft_putstr_fd(".triangle:\n{\n", fd);
			put_cl_fd("/b: ", winfo->obj[i].b, fd);
			put_cl_fd("/c: ", winfo->obj[i].b, fd);
		}
		else if (winfo->obj[i].type == 6)
		{
			ft_putstr_fd(".torus:\n{\n", fd);
			put_cl_fd("/dir: ", winfo->obj[i].b, fd);
			ft_putstr_fd("\t/max: ", fd);
			ft_putdouble_fd(winfo->obj[i].max, fd);
			ft_putchar_fd('\n', fd);
			ft_putstr_fd("\t/min: ", fd);
			ft_putdouble_fd(winfo->obj[i].min, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (winfo->obj[i].type == 7)
		{
			ft_putstr_fd(".holecube:\n{\n", fd);
			ft_putstr_fd("\t/r: ", fd);
			ft_putdouble_fd(winfo->obj[i].r, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (winfo->obj[i].type == 8)
		{
			ft_putstr_fd(".ellipsoid:\n{\n", fd);
			put_cl_fd("/b: ", winfo->obj[i].b, fd);
		}
		if (winfo->obj[i].type != 5)
			put_cl_fd("/pos: ", winfo->obj[i].a, fd);
		else
			put_cl_fd("/a: ", winfo->obj[i].a, fd);
		put_cl_fd("/color: ", winfo->obj[i].color, fd);
		ft_putstr_fd("\t/reflection: ", fd);
		ft_putdouble_fd(winfo->text[i].r, fd);
		ft_putchar_fd('\n', fd);
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
		i++;
	}
}
