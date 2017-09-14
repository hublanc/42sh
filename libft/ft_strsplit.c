/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:06:21 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 12:29:57 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int		count_word(char const *s, char c)
{
	int		isword;
	int		nb_w;

	isword = 0;
	nb_w = 0;
	while (*s)
	{
		if (isword == 0 && *s != c)
		{
			isword++;
			nb_w++;
		}
		if (isword == 1 && *s == c)
			isword = 0;
		s++;
	}
	return (nb_w);
}

static	int		getstrlen(char const *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tabstr;
	int		i;
	int		nb_w;

	if (!s)
		return (0);
	i = 0;
	nb_w = count_word(s, c);
	if (!(tabstr = (char**)malloc(sizeof(char*) * (nb_w + 1))))
		return (0);
	while (nb_w--)
	{
		while (*s == c && *s)
			s++;
		tabstr[i] = ft_strsub(s, 0, getstrlen(s, c));
		i++;
		s += getstrlen(s, c);
	}
	tabstr[i] = NULL;
	return (tabstr);
}
