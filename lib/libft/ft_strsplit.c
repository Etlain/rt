/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 15:56:14 by abara             #+#    #+#             */
/*   Updated: 2017/02/22 13:10:28 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lensize(const char *s, char c, size_t k)
{
	size_t	size;

	size = 0;
	while (s[k] != '\0' && s[k] == c)
	{
		k++;
	}
	while (s[k] != '\0' && s[k] != c)
	{
		size++;
		k++;
	}
	return (size);
}

static char		*ft_putin(const char *s, char c, size_t *x)
{
	char	*str;
	size_t	k;
	size_t	index;

	index = 0;
	k = *x;
	str = (char *)malloc(sizeof(*str) * (ft_lensize(s, c, k) + 1));
	if (!str)
		return (NULL);
	while (s[*x] != '\0' && s[*x] == c)
	{
		*x = *x + 1;
	}
	while (s[*x] != '\0' && s[*x] != c)
	{
		str[index] = s[*x];
		*x = *x + 1;
		index++;
	}
	str[index] = '\0';
	return (str);
}

static size_t	ft_nbwords(const char *s, char c)
{
	size_t	nb;
	size_t	index;
	size_t	i;

	index = 0;
	nb = 0;
	while (s[index] != '\0')
	{
		i = 0;
		while (s[index] == c)
			index++;
		if (s[index] == '\0')
			nb--;
		while (s[index] != c && s[index] != '\0')
		{
			index++;
			i++;
		}
		nb++;
	}
	return (nb);
}

char			**ft_strsplit(const char *s, char c)
{
	char		**tab;
	size_t		index;
	size_t		x;
	size_t		i;

	if (!s)
		return (NULL);
	i = ft_nbwords(s, c);
	x = 0;
	index = 0;
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (tab == NULL)
		return (NULL);
	while (index < i)
	{
		tab[index] = ft_putin(s, c, &x);
		index++;
	}
	tab[index] = NULL;
	return (tab);
}
