/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:15:20 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/14 10:03:12 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (0);
	while (n && *s1 && *s2 && *s1 == *s2)
	{
		n--;
		s1++;
		s2++;
	}
	if (!n)
		return (0);
	else
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
