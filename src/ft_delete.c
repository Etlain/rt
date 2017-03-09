/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:32:14 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/09 13:58:56 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	ft_delete_light(t_winfo *w, int id)
{
	t_light		*o;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (id < 0 || id >= w->file.nblight)
		return ;
	w->file.nblight--;
	o = (t_light *)malloc(sizeof(t_light) * w->file.nblight);
	while (i < w->file.nblight + 1)
	{
		if (i != id)
		{
			o[j] = w->light[i];
			j++;
		}
		i++;
	}
	free(w->light);
	w->light = o;
}

static void	fill_struct(t_winfo *w, t_object *o, t_text *t, int id)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < w->file.nbobj + 1)
	{
		if (i != id)
		{
			o[j] = w->obj[i];
			t[j] = w->text[i];
			j++;
		}
		i++;
	}
}

static void	ft_delete_object(t_winfo *w, int id)
{
	t_object	*o;
	t_text		*t;

	if (id < 0 || id >= w->file.nbobj)
		return ;
	w->file.nbobj--;
	o = (t_object *)malloc(sizeof(t_object) * w->file.nbobj);
	t = (t_text *)malloc(sizeof(t_text) * w->file.nbobj);
	fill_struct(w, o, t, id);
	free(w->obj);
	free(w->text);
	w->obj = o;
	w->text = t;
}

void		ft_delete(t_winfo *w, char *cmd)
{
	if (ft_strncmp("object", cmd, 6) == 0)
	{
		if (cmd[6] != ' ')
			ft_delete_object(w, w->opt.oselect);
		else
			ft_delete_object(w, ft_atoi(&cmd[7]));
	}
	else if (ft_strncmp("light", cmd, 5) == 0)
	{
		if (cmd[5] != ' ')
			ft_delete_light(w, w->opt.oselect);
		else
			ft_delete_light(w, ft_atoi(&cmd[6]));
	}
}
