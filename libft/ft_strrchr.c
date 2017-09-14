/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:36:11 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 19:29:15 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	while (*s != '\0')
	{
		s++;
	}
	while (s_len)
	{
		if (*s == (char)c)
		{
			return ((char*)s);
		}
		s--;
		s_len--;
	}
	if (*s == (char)c)
		return ((char*)s);
	return (0);
}
