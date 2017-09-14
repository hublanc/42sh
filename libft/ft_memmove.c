/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:10:21 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/10 15:39:58 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	current;

	if (dst != src)
	{
		if (dst < src)
		{
			current = 0;
			while (current != len)
			{
				*(((char*)dst) + current) = *(((char*)src) + current);
				current++;
			}
		}
		else
		{
			while (len)
			{
				*(((char*)dst) + (len - 1)) = *(((char*)src) + (len - 1));
				len--;
			}
		}
	}
	return (dst);
}
