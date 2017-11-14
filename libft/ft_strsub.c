/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:20:13 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/14 16:18:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*str1;
	size_t	i;

	if (!s || !*s || !*(s + start))
		return (NULL);
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
