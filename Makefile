NAME = RT

SRC =	main.c winfo.c press.c error.c parse.c check.c memory.c get_camera.c help.c \
		get_light.c get_object.c ensure.c vector.c draw.c render_cpu.c ray.c		\
		intersection.c calculate.c vector_s.c math.c light.c shadow.c press_nc.c	\
		press_c.c keycode.c ft_fxaa.c ft_rgbcmp.c ft_getpixel.c ft_putpixel_img.c	\
		execute.c file.c new_double.c degree_2.c cubic.c quartic.c torus.c ct.c		\
		ellipsoid.c render_gpu.c ft_create.c ft_delete.c ft_modify.c get_texture.c	\
		texture.c obj_t.c ft_link.c put_fd.c save_other.c

SRC_PATH = src/

LIB = lib/libft/libft.a

FLAGS = -lmlx -framework OpenGL -framework AppKit -framework OpenCL -lm

all: $(NAME)

$(NAME):
	make -C lib/libft/
	gcc -o $(NAME) -g $(addprefix $(SRC_PATH), $(SRC)) $(LIB) $(FLAGS)

clean:
	make clean -C lib/libft/

fclean: clean
	make fclean -C lib/libft/
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
