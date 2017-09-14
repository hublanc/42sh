/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:20:13 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 12:26:44 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*str1;
	size_t	i;

	str1 = (char*)s;
	i = 0;
	if (!s)
		return (0);
	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	while (i < len)
	{
		str[i] = str1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
