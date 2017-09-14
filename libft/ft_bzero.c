/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:57:15 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/04 10:37:06 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	zero;

	i = 0;
	ptr = s;
	zero = '\0';
	while (i < n)
	{
		*ptr = zero;
		ptr++;
		i++;
	}
}
