/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:45:10 by abara             #+#    #+#             */
/*   Updated: 2017/02/20 15:03:02 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/RT.h"

void	render_gpu(t_winfo *w)
{
	cl_mem	pixels_buffer;
	cl_mem	cam_buffer;
	cl_mem	obj_buffer;
	cl_mem	nbobj_buffer;
	cl_mem	light_buffer;
	cl_mem	nbl_buffer;
	int		*pixels;
	size_t	global;
	size_t	local;
	int		i;
	i = 0;

	global = W * H;
	local = 128;
	pixels = (int *)malloc(sizeof(int) * W * H * 4);

	pixels_buffer = clCreateBuffer(w->context, CL_MEM_WRITE_ONLY |
	CL_MEM_COPY_HOST_PTR, 4 * W * H * sizeof(int), pixels, NULL);
	cam_buffer = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, sizeof(t_cam), &w->cam, NULL);
	obj_buffer = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, w->file.nbobj * sizeof(t_object), w->obj, NULL);
	nbobj_buffer = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, sizeof(int), &w->file.nbobj, NULL);
	light_buffer = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, w->file.nblight * sizeof(t_light), w->light, NULL);
	nbl_buffer = clCreateBuffer(w->context, CL_MEM_READ_ONLY |
	CL_MEM_COPY_HOST_PTR, sizeof(int), &w->file.nblight, NULL);

	clSetKernelArg(w->kernel, 0, sizeof(pixels_buffer), (void*)&pixels_buffer);
	clSetKernelArg(w->kernel, 1, sizeof(cam_buffer), (void*)&cam_buffer);
	clSetKernelArg(w->kernel, 2, sizeof(obj_buffer), (void*)&obj_buffer);
	clSetKernelArg(w->kernel, 3, sizeof(nbobj_buffer), (void*)&nbobj_buffer);
	clSetKernelArg(w->kernel, 4, sizeof(light_buffer), (void*)&light_buffer);
	clSetKernelArg(w->kernel, 5, sizeof(nbl_buffer), (void*)&nbl_buffer);

	clEnqueueNDRangeKernel(w->queue, w->kernel, 1, NULL, &global, &local, 0, NULL, NULL);

	clEnqueueReadBuffer(w->queue, pixels_buffer, CL_TRUE, 0, 4 * W * H * sizeof(int), pixels, 0, NULL, NULL);

	clReleaseMemObject(pixels_buffer);
	clReleaseMemObject(cam_buffer);
	clReleaseMemObject(obj_buffer);
	clReleaseMemObject(nbobj_buffer);
	clReleaseMemObject(light_buffer);
	clReleaseMemObject(nbl_buffer);

	while (i < 4 * W * H)
	{
		w->data[i] = (char)pixels[i];
		i++;
	}

	if (w->opt.fxaa)
		ft_fxaa(w->img, W, H, w->opt.fxaa);

	mlx_put_image_to_window(w->mlx, w->win, w->img, 0, 0);
}
