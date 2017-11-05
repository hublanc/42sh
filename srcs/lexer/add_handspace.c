/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:18:48 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/31 17:06:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*add_handspace(const char *name)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (name[++i])
		if (name[i] == 32)
			j++;
	if (!(s = (char *)ft_memalloc(ft_strlen(name) + j + 1)))
		return (NULL);
	ft_strcat(s, name);
	i = -1;
	while (s[++i])
		if (s[i] == 32)
			saddchr(&s, '\\', i++);
	return (s);
}
