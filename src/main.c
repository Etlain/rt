/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:09:49 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:37:08 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

int	main(int argc, char **argv)
{
	t_winfo	w;

	if (argc != 2)
		print_error(6);
	init_winfo(&w, argv[1]);
	render_cpu(&w);
	mlx_mouse_hook(w.win, mouse_button, &w);
	mlx_hook(w.win, 2, 1, key_press, &w);
	mlx_loop(w.mlx);
	return (0);
}
