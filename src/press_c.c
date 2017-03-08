#include "../lib/RT.h"

void	press_console(t_winfo *w, int key)
{
	char	*tmp;

	if (ft_strlen(w->opt.cmd) < 70 && key != 51 && key != 50 && key != 36)
	{
		tmp = w->opt.cmd;
		w->opt.cmd = ft_strjoin(w->opt.cmd, get_keycode(key));
		ft_memdel((void**)&tmp);
		draw_console(w, w->opt.color);
		mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
		mlx_string_put(w->mlx, w->win, 0, H - 20, 0xffffff, w->opt.cmd);
	}
	else if (key == 51 && ft_strlen(w->opt.cmd) > 0)
	{
		w->opt.cmd[ft_strlen(w->opt.cmd) - 1] = '\0';
		draw_console(w, w->opt.color);
		mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
		mlx_string_put(w->mlx, w->win, 0, H - 20, 0xffffff, w->opt.cmd);
	}
	else if (key == 50)
	{
		w->opt.console = 0;
		render_cpu(w);
	}
	else if (key == 36)
	{
		exec(w, w->opt.cmd);
		ft_bzero(w->opt.cmd, ft_strlen(w->opt.cmd));
		w->opt.console = 0;
	}
}
