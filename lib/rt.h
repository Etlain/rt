/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:47:54 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/13 13:32:33 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define W 800
# define H 600

# include <math.h>
# include "libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <openCL/opencl.h>

typedef cl_double3		t_v;

typedef struct			s_uv
{
	t_v					d;
	double				u;
	double				v;
	double				j;
	double				k;
}						t_uv;

typedef struct			s_bufgpu
{
	cl_mem				pixels;
	cl_mem				cam;
	cl_mem				obj;
	cl_mem				nbobj;
	cl_mem				light;
	cl_mem				nbl;
}						t_bufgpu;

typedef struct			s_xy
{
	int					x;
	int					y;
}						t_xy;

typedef struct			s_ray
{
	t_v					color;
	t_v					a;
	t_v					dir;
	t_v					current;
	int					id;
	double				t;
}						t_ray;

typedef struct			s_cam
{
	t_v					pos;
	t_v					dir;
}						t_cam;

typedef struct			s_light
{
	t_v					pos;
	t_v					color;
}						t_light;

typedef struct			s_object
{
	t_v					color;
	t_v					a;
	t_v					b;
	t_v					c;
	double				r;
	double				min;
	double				max;
	int					type;
}						t_object;

typedef struct			s_texture
{
	unsigned int		w;
	unsigned int		h;
	unsigned char		*texture;
	char				*name;
}						t_texture;

typedef struct			s_text
{
	t_texture			texture;
	t_texture			normal;
	double				r;
	double				d;
}						t_text;

typedef struct			s_file
{
	char				**file;
	int					size;
	int					nbobj;
	int					nbcam;
	int					nblight;
	int					nbsphere;
	int					nbcylinder;
	int					nbplane;
	int					nbcone;
	int					nbtriangle;
	int					nbtorus;
	int					nbct;
	int					nbelli;
}						t_file;

typedef struct			s_option
{
	t_v					color;
	char				*cmd;
	int					oselect;
	int					lselect;
	char				console;
	char				render;
	char				sepia;
	char				fxaa;
	char				trt;
	char				ref;
	double				ambient;
	int					cshade;
	double				speed;
}						t_option;

typedef struct			s_winfo
{
	t_file				file;
	t_option			opt;
	t_cam				cam;
	t_light				*light;
	t_object			*obj;
	t_text				*text;
	t_ray				ray;
	void				*mlx;
	void				*win;
	void				*img;
	char				*data;
	char				*filename;
	int					bpp;
	int					line;
	int					endian;
	cl_platform_id		platform;
	cl_device_id		device;
	cl_kernel			kernel;
	cl_int				err;
	cl_context			context;
	cl_program			program;
	cl_command_queue	queue;
	char				*source;
}						t_winfo;

void					init_winfo(t_winfo *w, char *filename);
void					init_winfo_file(t_winfo *w, t_file *file);
int						key_press(int key, void *param);
int						mouse_button(int key, int x, int y, void *param);
void					print_error(int n);
void					parse_file(char *filename, t_file *file);
void					check_file(t_file *file);
void					free_memory(void **mem, int nb);
int						check_split(char **split, int nb);
void					get_split(t_v *v, char **file, int x, int y);
char					*del_space(char *str, int i);
int						get_camera(t_winfo *w);
void					get_light(t_winfo *w);
void					get_object(t_winfo *w);
void					get_objecttexture(t_winfo *w);
void					ensure_object(t_object *obj);
void					ensure_light(t_light *light);
void					ensure_texture(t_text *text);
t_v						set_v(double x, double y, double z);
double					norm_v(t_v v);
t_v						normalize(t_v v);
t_v						get_v(t_v a, t_v b);
void					put_pixel(t_winfo *w, int x, int y, t_v color);
void					put_pixel_sepia(t_winfo *w, int x, int y, t_v color);
void					draw_console(t_winfo *w, t_v color);
void					render_cpu(t_winfo *w);
void					set_vrep(t_v d, t_v *v);
void					render_gpu(t_winfo *w);
t_v						reflection(t_ray ray, t_winfo *w, int *nb, int depth);
void					intersection(t_ray *ray, t_object *obj, int nbobj);
double					check_sphere(t_ray *ray, t_object obj);
double					check_cylinder(t_ray *ray, t_object obj);
double					check_plane(t_ray *ray, t_object *obj);
double					check_cone(t_ray *ray, t_object obj);
double					check_triangle(t_ray *ray, t_object *obj);
double					get_t_a(double delta, double a, double b);
double					get_t_b(t_object *obj, t_ray *ray, double delta,
						double *ab);
t_v						limit_v(t_v v, double min, double max);
double					dpower(double n, double t);
double					dot(t_v v1, t_v v2);
t_v						cross(t_v v1, t_v v2);
t_v						add_v(t_v a, t_v b);
t_v						mult_v(t_v a, double b);
t_v						invert_v(t_v v);
void					check_light(t_winfo *w, t_light *l, t_ray *ray,
						t_object *obj);
void					get_normal(t_ray *ray, t_object *obj);
t_v						get_normal_other(t_ray *ray, t_object *obj, t_light l);
double					shadow(t_light *l, t_ray ray, t_object *obj, int *nb);
void					press_noconsole(t_winfo *w, int key);
void					press_console(t_winfo *w, int key);
void					ft_fxaa(void *img, int w, int h, int i);
double					ft_rgbcmp(int ca, int cb);
void					ft_putpixel_img(void *img, int x, int y, int c);
int						ft_getpixel(void *img, int x, int y);
void					save_file(char *name, t_winfo *winfo);
void					exec(t_winfo *winfo, char *cmd);
void					get_nbr(t_v *t, char *str);
void					exec3(t_winfo *winfo, char *cmd);
char					*get_keycode(int key);
int						degree_2(double *pol, double *res);
int						cubic(double *pol, double *res);
int						quartic(double *pol, double *res);
double					*new_double(int nbr);
double					check_torus(t_ray *ray, t_object obj);
t_v						normal_torus(t_ray *ray, t_object *obj);
double					ft_condition(double *res, int max);
double					check_ellipsoid(t_ray *ray, t_object obj);
t_v						normal_ellipsoid(t_ray *ray, t_object *obj);
double					check_ct(t_ray *ray, t_object obj);
t_v						normal_ct(t_ray *ray, t_object *obj);
void					ft_create(t_winfo *winfo, char *cmd);
void					ft_modify(t_winfo *w, char *cmd);
void					ft_delete(t_winfo *w, char *cmd);
void					get_texture(t_texture *texture, char *filename);
t_v						plane_t(t_object *obj, t_texture *text, t_v p);
t_v						sphere_t(t_object *obj, t_texture *text, t_v p);
void					ft_link(t_winfo *winfo, char *cmd);
void					put_cl_fd(char *str, t_v val, int fd);
void					put_nb_fd(char *str, double nb, int fd, int i);
void					save_other(t_winfo *winfo, int fd, int i);
t_v						get_texel(t_texture t, int i, int j);
void					get_uv_texture(t_winfo *w);
double					limitation(double v, double min, double max);
t_v						get_uv_normal(t_winfo *w, t_v n);
t_v						apply_nmap(t_v v, t_v c);
unsigned char			*ft_ustrncpy_f(unsigned char *dest,
						const unsigned char *src, size_t n);
unsigned int			get_from_data(unsigned int pos, unsigned char *data);
t_v						v_mult_v(t_v a, t_v b);

#endif
