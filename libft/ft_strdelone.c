/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:11:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/13 20:21:24 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdelone(char *str, int pos)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (str);
	if (!ft_strlen(str))
		new = ft_strnew(0);
	else
		new = ft_strnew(ft_strlen(str) - 1);
	while (str[i])
	{
		if ((i + 1) != pos)
			new[j++] = str[i];
		i++;
	}
	if (*new == '\0')
		ft_strdel(&new);
	ft_strdel(&str);
	return (new);
}
