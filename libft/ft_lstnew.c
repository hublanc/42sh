/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:29:18 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 14:17:45 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_item;
	void	*cpy_content;
	size_t	cpy_size;

	if (!(new_item = (t_list*)malloc(sizeof(t_list))))
		return (0);
	if (content)
	{
		cpy_content = ft_memalloc(content_size);
		cpy_size = content_size;
		ft_memcpy(cpy_content, content, content_size);
		new_item->content_size = cpy_size;
		new_item->content = cpy_content;
	}
	else
	{
		new_item->content = NULL;
		new_item->content_size = 0;
	}
	new_item->next = NULL;
	return (new_item);
}
