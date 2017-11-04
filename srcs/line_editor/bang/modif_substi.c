/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_substi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:19:00 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 19:32:01 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	modif_substi3(int *i, int *j, char *new, int rec)
{
	*i = -1;
	*j = 0;
	while (new[++(*i)] && (*j == 0 || rec > 0))
		if (new[*i] == '&' && (*i <= 0 || new[*i - 1] != '\\'))
			(*j)++;
}

static void	modif_substi2(char *new, char **s, int k, char *old)
{
	if (!ft_strchr(new, '&'))
		ft_strcat(*s, new);
	else
	{
		k = 0;
		while (new[k])
		{
			if (new[k] == '&' && (k <= 0 || new[k - 1] == '\\'))
				ft_strcat(*s, old);
			else
				(*s)[ft_strlen(*s)] = new[k];
		}
	}
}

char		*modif_substi(char *arg, char *old, char *new, int rec)
{
	char	*s;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!arg || !old || !new)
		return (NULL);
	modif_substi3(&i, &j, new, rec);
	init_substi1(&i, &k, old, j);
	init_substi2(&j, &l, arg);
	while ((i == 0 || rec > 0) && i < l && (i += ft_strstr_len(arg + i, old)))
		loop_substi(&i, &j, old);
	if (!(s = (char *)ft_memalloc(sizeof(char) + (l - j * ft_strlen(old) + k * j
						+ j * ft_strlen(new) + 1))))
		return (NULL);
	init_substi3(&i, &j, &l, arg);
	while ((i == 0 || rec > 0) && i < l && (i = ft_strstr_len(arg + j, old)))
	{
		ft_strncat(s, arg + j, i);
		j += i + ft_strlen(old);
		modif_substi2(new, &s, k, old);
	}
	j < l ? ft_strcat(s, arg + j) : 0;
	return (s);
}
