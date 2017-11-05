/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:38:16 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/10 20:47:15 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*save_s1;
	unsigned char	*save_s2;

	save_s1 = (unsigned char*)s1;
	save_s2 = (unsigned char*)s2;
	while (n)
	{
		if (*save_s1 != *save_s2)
			return (*save_s1 - *save_s2);
		n--;
		save_s1++;
		save_s2++;
	}
	return (0);
}
