/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:12:21 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/12 12:23:54 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	if (!(str = (char *)ft_memalloc(n + 1)))
		return (NULL);
	ft_memcpy(str, s1, n);
	return (str);
}
