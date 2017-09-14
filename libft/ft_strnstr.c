/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:04:49 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/08 21:02:58 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*debut;
	char	*substr;
	size_t	i;

	while (*big && len > 0)
	{
		debut = (char*)big;
		substr = (char*)little;
		i = len;
		while (*big && *substr && *big == *substr && i > 0)
		{
			substr++;
			big++;
			i--;
		}
		if (!*substr)
			return (debut);
		big = debut + 1;
		len--;
	}
	return (0);
}
