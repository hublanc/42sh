/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 18:38:38 by hublanc           #+#    #+#             */
/*   Updated: 2017/01/12 15:53:25 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t size)
{
	unsigned char	*new;
	unsigned char	*cpy;

	if (!size)
		return (ptr);
	cpy = (unsigned char*)ptr;
	if (!(new = (unsigned char*)ft_strnew(ft_strlen((char*)cpy) + size)))
		return (NULL);
	ft_strcpy((char*)new, (char*)cpy);
	if (ptr)
		ft_memdel(&ptr);
	cpy = NULL;
	return ((void*)new);
}
