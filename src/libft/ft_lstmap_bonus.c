/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rpicot <rpicot@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:24:54 by rpicot        #+#    #+#                 */
/*   Updated: 2022/02/23 16:24:55 by rpicot        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	newlist = NULL;
	tmp = newlist;
	while (lst)
	{
		newlist = ft_lstnew((*f)(lst->content));
		if (!newlist)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&tmp, newlist);
	}
	return (tmp);
}
