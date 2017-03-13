/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:07:02 by abara             #+#    #+#             */
/*   Updated: 2017/03/13 15:04:30 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void		get_nbr(t_v *t, char *str)
{
	char **tab;

	tab = ft_strsplit(str, ' ');
	if (check_split(tab, 3))
	{
		t->x = ft_atod(tab[0]);
		t->y = ft_atod(tab[1]);
		t->z = ft_atod(tab[2]);
	}
	ft_free_tab(tab);
}

static void	get_id(t_winfo *winfo, char *str)
{
	char	*elem;
	int		nb;

	elem = ft_strtrim(str);
	if (ft_strncmp("light ", elem, 6) == 0)
	{
		nb = ft_atoi(&elem[6]);
		if (nb >= 0 && nb < winfo->file.nblight)
			winfo->opt.lselect = nb;
		free(elem);
	}
	else if (ft_strncmp("object ", elem, 7) == 0)
	{
		nb = ft_atoi(&elem[7]);
		if (nb >= 0 && nb < winfo->file.nbobj)
			winfo->opt.oselect = nb;
		free(elem);
	}
}

void		exec3(t_winfo *winfo, char *cmd)
{
	char *elem;

	if (ft_strncmp("select ", cmd, 7) == 0)
		get_id(winfo, &cmd[7]);
	else if (ft_strncmp("loadlog ", cmd, 8) == 0)
	{
		elem = del_space(cmd, 8);
		init_winfo_file(winfo, &winfo->file);
		parse_file(elem, &winfo->file);
		winfo->filename = elem;
		check_file(&winfo->file);
		get_camera(winfo);
		get_light(winfo);
		get_object(winfo);
		free(elem);
	}
	else if (ft_strncmp("color ", cmd, 5) == 0)
	{
		elem = ft_strtrim(&cmd[6]);
		if (ft_strncmp("object ", elem, 7) == 0 && winfo->opt.oselect != -1)
			get_nbr(&winfo->obj[winfo->opt.oselect].color, &elem[7]);
		else if (ft_strncmp("light ", elem, 6) == 0)
			get_nbr(&winfo->light[winfo->opt.lselect].color, &elem[6]);
		free(elem);
	}
}

static void	exec2(t_winfo *winfo, char *cmd)
{
	if (ft_strncmp("speed", cmd, 5) == 0)
		winfo->opt.speed = ft_atod(&cmd[5]);
	else if (ft_strncmp("cpu", cmd, 3) == 0)
		winfo->opt.render = 0;
	else if (ft_strncmp("gpu", cmd, 3) == 0)
		winfo->opt.render = 1;
	else if (ft_strncmp("link ", cmd, 5) == 0)
		ft_link(winfo, &cmd[5]);
	else if (ft_strncmp("create ", cmd, 7) == 0)
		ft_create(winfo, cmd);
	else if (ft_strncmp("delete ", cmd, 7) == 0)
		ft_delete(winfo, &cmd[7]);
	else if (ft_strncmp("nbref ", cmd, 6) == 0)
		winfo->opt.ref = ft_atoi(&cmd[6]);
	else if (winfo->opt.oselect != -1)
		ft_modify(winfo, cmd);
	else
		exec3(winfo, cmd);
}

void		exec(t_winfo *winfo, char *cmd)
{
	char	**tab;
	char	*elem;
	char	*tmp;
	int		ret;

	if (ft_strncmp("savelog", cmd, 7) == 0)
	{
		elem = del_space(cmd, 7);
		if (elem[0] != '\0')
			save_file(elem, winfo);
		else if (winfo->filename != NULL)
			save_file(winfo->filename, winfo);
		free(elem);
	}
	else if (ft_strncmp("fxaa", cmd, 4) == 0)
		winfo->opt.fxaa = ft_atoi(&cmd[4]);
	else if (ft_strncmp("sepia", cmd, 5) == 0)
		winfo->opt.sepia = ft_atoi(&cmd[5]);
	else if (ft_strncmp("cellshading", cmd, 11) == 0)
		winfo->opt.cshade = ft_atoi(&cmd[11]);
	else if (ft_strncmp("ambient", cmd, 7) == 0)
		winfo->opt.ambient = ft_atod(&cmd[7]);
	else
		exec2(winfo, cmd);
	render_cpu(winfo);
}
