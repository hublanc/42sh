/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 21:02:26 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/07 09:34:04 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*save_s;

	save_s = (unsigned char*)s;
	while (n)
	{
		if (*save_s == (unsigned char)c)
			return (save_s);
		n--;
		save_s++;
	}
	return (0);
}
