/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 19:27:52 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 16:35:51 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*newlst;
	t_list		*tmp;
	t_list		*modlst;

	tmp = f(lst);
	if ((modlst = ft_lstnew(tmp->content, tmp->content_size)) && (lst || f))
	{
		newlst = modlst;
		lst = lst->next;
		while (lst)
		{
			tmp = f(lst);
			if (!(modlst->next = ft_lstnew(tmp->content, tmp->content_size)))
				return (NULL);
			modlst = modlst->next;
			lst = lst->next;
		}
		modlst->next = NULL;
		return (newlst);
	}
	return (NULL);
}
