/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:09:56 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:40:44 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static int	check_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (filename[len - 1] != 'g')
		return (-1);
	else if (filename[len - 2] != 'o')
		return (-1);
	else if (filename[len - 3] != 'l')
		return (-1);
	else if (filename[len - 4] != '.')
		return (-1);
	return (0);
}

void		parse_file(char *filename, t_file *file)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if (check_filename(filename) == -1)
		print_error(1);
	if ((fd = open(filename, O_RDONLY)) < 0)
		print_error(2);
	while (get_next_line(fd, &line) > 0)
	{
		ft_memdel((void**)&line);
		file->size++;
	}
	if (file->size < 0)
		print_error(5);
	if (file->size > 0)
		ft_memdel((void**)&line);
	file->file = (char**)malloc(sizeof(char*) * file->size + 1);
	file->file[file->size] = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		print_error(2);
	while (get_next_line(fd, &file->file[i]) > 0)
		i++;
}
