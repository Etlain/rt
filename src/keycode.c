/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:36:57 by abara             #+#    #+#             */
/*   Updated: 2017/03/09 11:36:42 by mmouhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/rt.h"

static char	*get_first(int key)
{
	if (key == 0)
		return ("a");
	else if (key == 1)
		return ("s");
	else if (key == 2)
		return ("d");
	else if (key == 3)
		return ("f");
	else if (key == 4)
		return ("h");
	else if (key == 5)
		return ("g");
	else if (key == 6)
		return ("z");
	else if (key == 7)
		return ("x");
	else if (key == 8)
		return ("c");
	else if (key == 9)
		return ("v");
	else if (key == 11)
		return ("b");
	return ("\0");
}

static char	*get_second(int key)
{
	if (key == 12)
		return ("q");
	else if (key == 13)
		return ("w");
	else if (key == 14)
		return ("e");
	else if (key == 15)
		return ("r");
	else if (key == 16)
		return ("y");
	else if (key == 17)
		return ("t");
	else if (key == 49)
		return (" ");
	else if (key == 27)
		return ("-");
	return ("\0");
}

static char	*get_third(int key)
{
	if (key == 31)
		return ("o");
	else if (key == 32)
		return ("u");
	else if (key == 34)
		return ("i");
	else if (key == 35)
		return ("p");
	else if (key == 37)
		return ("l");
	else if (key == 38)
		return ("j");
	else if (key == 40)
		return ("k");
	else if (key == 45)
		return ("n");
	else if (key == 46)
		return ("m");
	else if (key == 47)
		return (".");
	else if (key == 44)
		return ("/");
	return ("\0");
}

static char	*get_last(int key)
{
	if (key == 82)
		return ("0");
	else if (key == 83)
		return ("1");
	else if (key == 84)
		return ("2");
	else if (key == 85)
		return ("3");
	else if (key == 86)
		return ("4");
	else if (key == 87)
		return ("5");
	else if (key == 88)
		return ("6");
	else if (key == 89)
		return ("7");
	else if (key == 91)
		return ("8");
	else if (key == 92)
		return ("9");
	return ("\0");
}

char		*get_keycode(int key)
{
	if ((key >= 0 && key <= 9) || (key == 11))
		return (get_first(key));
	else if ((key >= 12 && key <= 17) || key == 49 || key == 27)
		return (get_second(key));
	else if ((key >= 31 && key <= 46) || key == 47 || key == 44)
		return (get_third(key));
	else if (key >= 82 && key <= 92)
		return (get_last(key));
	return ("\0");
}
