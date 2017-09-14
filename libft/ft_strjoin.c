/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:51:37 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 12:28:54 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	char	*concat(char *str1, char *str2, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	while (*str1)
	{
		str[i] = *str1;
		str1++;
		i++;
	}
	while (*str2)
	{
		str[i] = *str2;
		str2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*str1;
	char		*str2;

	if (!s1 || !s2)
		return (0);
	str1 = (char*)s1;
	str2 = (char*)s2;
	len = ft_strlen(s1) + ft_strlen(s2);
	return (concat(str1, str2, len));
}
