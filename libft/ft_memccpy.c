/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:22:23 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 17:57:13 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*str;
	char		*str1;
	size_t		i;
	char		ch;

	i = 0;
	ch = (unsigned char)c;
	str = (char*)dst;
	str1 = (char*)src;
	while (i < n)
	{
		str[i] = str1[i];
		dst++;
		if (str1[i] == ch)
			return (dst);
		i++;
	}
	return (0);
}
