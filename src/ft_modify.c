/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:37:01 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/13 15:10:35 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

void	ft_modify(t_winfo *w, char *cmd)
{
	if (ft_strncmp("pos ", cmd, 4) == 0)
		get_nbr(&w->obj[w->opt.oselect].a, &cmd[4]);
	else if (ft_strncmp("dir ", cmd, 4) == 0)
		get_nbr(&w->obj[w->opt.oselect].b, &cmd[4]);
	else if (ft_strncmp("normal ", cmd, 7) == 0)
		get_nbr(&w->obj[w->opt.oselect].c, &cmd[7]);
	else if (ft_strncmp("r ", cmd, 2) == 0)
		w->obj[w->opt.oselect].r = ft_atod(&cmd[2]);
	else if (ft_strncmp("min ", cmd, 4) == 0)
		w->obj[w->opt.oselect].min = ft_atod(&cmd[4]);
	else if (ft_strncmp("max ", cmd, 4) == 0)
		w->obj[w->opt.oselect].max = ft_atod(&cmd[4]);
	else if (ft_strncmp("nmap ", cmd, 5) == 0)
		get_texture(&w->text[w->opt.oselect].normal, &cmd[5]);
	else if (ft_strncmp("texture ", cmd, 8) == 0)
		get_texture(&w->text[w->opt.oselect].texture, &cmd[8]);
	else if (ft_strncmp("reflection ", cmd, 11) == 0)
		w->text[w->opt.oselect].r = ft_atod(&cmd[11]);
	else
		exec3(w, cmd);
}
