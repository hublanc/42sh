/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:15:20 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/14 10:17:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 == *s2 && *s1 && *s2)
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
