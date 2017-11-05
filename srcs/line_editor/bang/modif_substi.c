/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_substi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:19:00 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/05 11:38:21 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	modif_substi3(int *i, int *j, char *new)
{
	*i = -1;
	*j = 0;
	while (new[++(*i)])
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
	int		i[4];

	if (!arg || !old)
		return (NULL);
	modif_substi3(&(i[0]), &(i[1]), new);
	init_substi1(&(i[0]), &(i[2]), old, i[1]);
	init_substi2(&(i[1]), &(i[3]), arg);
	while ((i[1] == 0 || rec > 0) && i[0] < i[3] && (i[0] +=
			ft_strstr_len(arg + i[0], old)) >= 0)
		loop_substi(&(i[0]), &(i[1]), old);
	if (!(s = (char *)ft_memalloc(sizeof(char) + (i[3] - i[1] *
				ft_strlen(old) + i[2] * i[1] + i[1] * ft_strlen(new) + 1))))
		return (NULL);
	init_substi3(&i[0], &i[1], &i[3], arg);
	while ((i[1] == 0 || rec > 0) && i[0] < i[3] && ((i[0] =
					ft_strstr_len(arg + i[1], old)) || i[1] == 0))
	{
		i[0] ? ft_strncat(s, arg + i[1], i[0]) : 0;
		i[1] += i[0] + ft_strlen(old);
		modif_substi2(new, &s, i[2], old);
	}
	i[1] < i[3] ? ft_strcat(s, arg + i[1]) : 0;
	return (s);
}
