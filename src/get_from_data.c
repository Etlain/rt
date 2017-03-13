/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmouhssi <mmouhssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:57:26 by mmouhssi          #+#    #+#             */
/*   Updated: 2017/03/13 13:01:04 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

unsigned int		get_from_data(unsigned int pos, unsigned char *data)
{
	data = data + pos;
	return (*(unsigned int*)data);
}
