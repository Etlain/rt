/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abara <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 16:57:58 by abara             #+#    #+#             */
/*   Updated: 2015/12/11 14:58:36 by abara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlist;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	newlist = tmp;
	while (lst->next)
	{
		lst = lst->next;
		newlist->next = f(lst);
		newlist = newlist->next;
	}
	newlist->next = NULL;
	return (tmp);
}
