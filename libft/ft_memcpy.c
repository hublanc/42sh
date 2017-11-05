/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:41:11 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/10 10:19:21 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;
	char	*str2;
	size_t	i;

	i = 0;
	str = (char*)dst;
	str2 = (char*)src;
	while (i < n)
	{
		str[i] = str2[i];
		i++;
	}
	return (dst);
}
