/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strschr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:42:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/03 14:15:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strschr_len(char *s, char *s2)
{
	size_t	i;
	size_t	j;

	if (!s || !s2)
		return (0);
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s2[j] && s[i++] == s2[j])
			j++;
		if (!s2[j])
			return (i - j);
		else
			i -= j;
	}
	return (0);
}
