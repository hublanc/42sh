/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:15:22 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 12:31:06 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	void	getlen(char const *s, int *i, int *len)
{
	int		cmpt;
	int		length;

	length = *len;
	cmpt = *i;
	while (s[length - 1] == ' ' || s[length - 1] == '\n'
			|| s[length - 1] == '\t')
		length--;
	while (s[cmpt] == ' ' || s[cmpt] == '\n' || s[cmpt] == '\t')
	{
		length--;
		cmpt++;
	}
	*i = cmpt;
	*len = length;
	return ;
}

char			*ft_strtrim(char const *s)
{
	int		len;
	int		i;
	char	*str;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	getlen(s, &i, &len);
	if (len <= 0)
		len = 0;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	s += i;
	i = 0;
	while (i < len)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}
