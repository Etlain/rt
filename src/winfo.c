/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winfo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <abara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:10:09 by abara             #+#    #+#             */
/*   Updated: 2017/03/08 14:25:58 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

void		init_winfo_file(t_winfo *w, t_file *file)
{
	w->cam.pos.x = 0;
	w->cam.pos.y = 0;
	w->cam.pos.z = 0;
	w->cam.dir.x = 0;
	w->cam.dir.y = 0;
	w->cam.dir.z = 1;
	w->opt.color = set_v(0, 0, 0);
	w->opt.cmd = ft_strnew(70);
	w->opt.oselect = -1;
	w->opt.lselect = 0;
	w->opt.console = 0;
	w->opt.speed = 10;
	w->opt.render = 0;
	w->opt.sepia = 0;
	w->opt.fxaa = 0;
	w->opt.trt = 0;
	w->opt.ref = 1;
	file->size = 0;
	file->nbobj = 0;
	file->nbcam = 0;
	file->nblight = 0;
	file->nbsphere = 0;
	file->nbcylinder = 0;
	file->nbplane = 0;
	file->nbcone = 0;
	file->nbtriangle = 0;
	file->nbtorus = 0;
	file->nbelli = 0;
	file->nbct = 0;
}

static char *get_source(char *filename)
{
	char	*dst;
	int		size;
	int		fd;
	char	buf;

	size = 0;
	fd = open(filename, O_RDONLY);
	while (read(fd, &buf, 1) > 0)
		size++;
	dst = (char *)malloc(sizeof(char) * size + 1);
	size = 0;
	fd = open(filename, O_RDONLY);
	while (read(fd, &buf, 1) > 0)
	{
		dst[size] = buf;
		size++;
	}
	dst[size] = '\0';
	return (dst);
}

void		get_opencl_winfo(t_winfo *w)
{
	int		index;

	index = 0;
	w->source = get_source("render.cl");

	clGetPlatformIDs(1, &w->platform, NULL);
	clGetDeviceIDs(w->platform, CL_DEVICE_TYPE_GPU, 1, &w->device, NULL);

	w->context = clCreateContext(0, 1, &w->device, NULL, NULL, &w->err);
	printf("error: %d.\n", w->err);
	w->queue = clCreateCommandQueue(w->context, w->device, 0, &w->err);
	printf("error: %d.\n", w->err);
	w->program = clCreateProgramWithSource(w->context, 1, (const char **)&w->source, NULL, NULL);

	clBuildProgram(w->program, 1, &w->device, NULL, NULL, NULL);
	w->kernel = clCreateKernel(w->program, "render_gpu", &w->err);
	printf("error: %d.\n", w->err);
	ft_memdel((void**)&w->source);
}

void		init_winfo(t_winfo *w, char *filename)
{
	int	i;

	i = 0;
	w->mlx = mlx_init();
	w->win = mlx_new_window(w->mlx, W, H, "Raytracer");
	w->img = mlx_new_image(w->mlx, W, H);
	w->data = mlx_get_data_addr(w->img, &w->bpp, &w->line, &w->endian);
	w->filename = filename;
	init_winfo_file(w, &w->file);
	parse_file(w->filename, &w->file);
	check_file(&w->file);
	get_camera(w);
	get_light(w);
	get_object(w);
	get_objecttexture(w);
	get_opencl_winfo(w);
}
