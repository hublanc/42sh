/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:30:24 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/25 15:32:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	str = (char*)s1;
	if (!(copy = (char*)ft_memalloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
