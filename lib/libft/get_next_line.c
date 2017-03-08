/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:31:51 by abara             #+#    #+#             */
/*   Updated: 2016/09/30 11:03:08 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_list(t_list *list, int fd)
{
	t_list	*elem;
	t_list	*tmp;

	elem = malloc(sizeof(t_list));
	tmp = list;
	elem->content_size = fd;
	elem->content = NULL;
	elem->next = NULL;
	if (list)
	{
		while (list)
		{
			if (list->content_size == (size_t)fd)
			{
				ft_memdel((void**)&elem);
				return (list);
			}
			list = list->next;
		}
		list = tmp;
		while (list->next)
			list = list->next;
		list->next = elem;
	}
	return (elem);
}

int				line_size(char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0' && str[index] != '\n')
		index++;
	return (index);
}

char			*get_file(int const fd, int *check, char *str)
{
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			index;

	index = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	if (!str)
		str = ft_strnew(BUFF_SIZE + 1);
	while ((*check = read(fd, buf, BUFF_SIZE)) > 0)
	{
		tmp = str;
		str = ft_strjoin(str, buf);
		ft_strdel(&tmp);
		ft_bzero(buf, BUFF_SIZE + 1);
		while (str[index] != '\0')
		{
			if (str[index] == '\n')
				return (str);
			index++;
		}
	}
	return (str);
}

char			*get_dst(int *i, char **str)
{
	char	*dst;
	int		test;

	test = 0;
	while ((*str)[*i] != '\0' && (*str)[*i] != '\n')
		(*i)++;
	dst = ft_strsub(*str, 0, *i);
	if (*i == 0 && (*str)[0] == '\n')
		test = 1;
	if ((*str)[*i] != '\0')
		ft_strcpy(*str, &(*str)[*i + 1]);
	else
		ft_bzero(*str, *i);
	if (test == 0 && *i == 0)
		*i = 0;
	else if (test == 1)
		(*i)++;
	return (dst);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*list;
	t_list			*tmp;
	char			*dst;
	int				check;
	int				i;

	i = 0;
	check = 0;
	tmp = list;
	if (fd < 0 || !line)
		return (-1);
	list = ft_list(list, fd);
	list->content = get_file(fd, &check, list->content);
	if (check == -1)
		return (-1);
	dst = get_dst(&i, (char**)&list->content);
	if (tmp)
		list = tmp;
	if (i > 0)
	{
		*line = dst;
		return (1);
	}
	ft_memdel((void**)&dst);
	return (0);
}
