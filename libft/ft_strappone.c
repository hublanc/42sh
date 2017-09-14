/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 10:52:07 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 14:34:02 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strappone(char *str, char c, int pos)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (ft_strdup(&c));
	else
		new = ft_strnew(ft_strlen(str) + 1);
	while (j < ((int)ft_strlen(str)) + 1)
	{
		if (j != pos)
			new[j++] = str[i++];
		else
			new[j++] = c;
	}
	ft_strdel(&str);
	return (new);
}
