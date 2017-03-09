/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 14:56:20 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 13:07:58 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void		get_nb(char *cmd, int *id_a, int *id_b)
{
	char **tab;

	tab = ft_strsplit(cmd, ' ');
	if (check_split(tab, 2))
	{
		*id_a = ft_atoi(tab[0]);
		*id_b = ft_atoi(tab[1]);
	}
	ft_free_tab(tab);
}

static void		ft_link3(t_winfo *winfo, char *cmd)
{
	int id_a;
	int id_b;

	id_a = -1;
	id_b = -1;
	if (ft_strncmp("b ", cmd, 2) == 0)
	{
		get_nb(&cmd[2], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].b = winfo->obj[id_a].b;
	}
	else if (ft_strncmp("c ", cmd, 2) == 0)
	{
		get_nb(&cmd[2], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].c = winfo->obj[id_a].c;
	}
}

static void		ft_link2(t_winfo *winfo, char *cmd)
{
	int id_a;
	int id_b;

	id_a = -1;
	id_b = -1;
	if (ft_strncmp("dir ", cmd, 4) == 0)
	{
		get_nb(&cmd[4], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].b = winfo->obj[id_a].b;
	}
	else if (ft_strncmp("normal ", cmd, 7) == 0)
	{
		get_nb(&cmd[7], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].c = winfo->obj[id_a].c;
	}
	else if (ft_strncmp("a ", cmd, 2) == 0)
	{
		get_nb(&cmd[2], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].a = winfo->obj[id_a].a;
	}
	else
		ft_link3(winfo, cmd);
}

void			ft_link(t_winfo *winfo, char *cmd)
{
	int id_a;
	int id_b;

	id_a = -1;
	id_b = -1;
	if (ft_strncmp("r ", cmd, 2) == 0)
	{
		get_nb(&cmd[2], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].r = winfo->obj[id_a].r;
	}
	else if (ft_strncmp("pos ", cmd, 4) == 0)
	{
		get_nb(&cmd[4], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].a = winfo->obj[id_a].a;
	}
	else if (ft_strncmp("color ", cmd, 6) == 0)
	{
		get_nb(&cmd[6], &id_a, &id_b);
		if (id_a != -1 && id_b != -1)
			winfo->obj[id_b].color = winfo->obj[id_a].color;
	}
	else
		ft_link2(winfo, cmd);
}
