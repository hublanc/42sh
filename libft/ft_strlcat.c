/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:01:25 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/09 10:36:45 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	n;
	char	*d;
	char	*s;

	s = (char*)src;
	d = dst;
	n = size;
	while (n-- && *d)
		d++;
	dest_len = d - dst;
	n = size - dest_len;
	if (!n)
		return (dest_len + ft_strlen(src));
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (dest_len + ft_strlen(src));
}
