/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:45:10 by abara             #+#    #+#             */
/*   Updated: 2017/03/10 16:34:20 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static void	create_buff(t_winfo *w, t_bufgpu *buff, int *pixels)
{
	buff->pixels = clCreateBuffer(w->context, CL_MEM_WRITE_ONLY |
	CL_MEM_COPY_HOST_PTR, 4 * W * H * sizeof(int), pixels, NULL);
	buff->cam = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, sizeof(t_cam), &w->cam, NULL);
	buff->obj = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, w->file.nbobj * sizeof(t_object), w->obj, NULL);
	buff->nbobj = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, sizeof(int), &w->file.nbobj, NULL);
	buff->light = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, w->file.nblight * sizeof(t_light), w->light, NULL);
	buff->nbl = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, sizeof(int), &w->file.nblight, NULL);
}

static void	set_buff(t_winfo *w, t_bufgpu *buff)
{
	clSetKernelArg(w->kernel, 0, sizeof(buff->pixels), (void*)&buff->pixels);
	clSetKernelArg(w->kernel, 1, sizeof(buff->cam), (void*)&buff->cam);
	clSetKernelArg(w->kernel, 2, sizeof(buff->obj), (void*)&buff->obj);
	clSetKernelArg(w->kernel, 3, sizeof(buff->nbobj), (void*)&buff->nbobj);
	clSetKernelArg(w->kernel, 4, sizeof(buff->light), (void*)&buff->light);
	clSetKernelArg(w->kernel, 5, sizeof(buff->nbl), (void*)&buff->nbl);
}

static void	release_buff(t_bufgpu *buff)
{
	clReleaseMemObject(buff->pixels);
	clReleaseMemObject(buff->cam);
	clReleaseMemObject(buff->obj);
	clReleaseMemObject(buff->nbobj);
	clReleaseMemObject(buff->light);
	clReleaseMemObject(buff->nbl);
}

void		render_gpu(t_winfo *w)
{
	t_bufgpu	buff;
	int			*pixels;
	size_t		global;
	size_t		local;
	int			i;

	i = 0;
	global = W * H;
	local = 128;
	pixels = (int *)malloc(sizeof(int) * W * H * 4);
	create_buff(w, &buff, pixels);
	set_buff(w, &buff);
	clEnqueueNDRangeKernel(w->queue, w->kernel, 1, NULL, &global, &local, 0,
			NULL, NULL);
	clEnqueueReadBuffer(w->queue, buff.pixels, CL_TRUE, 0, 4 * W * H *
			sizeof(int), pixels, 0, NULL, NULL);
	release_buff(&buff);
	while (i < 4 * W * H)
	{
		w->data[i] = (char)pixels[i];
		i++;
	}
	if (w->opt.fxaa)
		ft_fxaa(w->img, W, H, w->opt.fxaa);
	mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
}
