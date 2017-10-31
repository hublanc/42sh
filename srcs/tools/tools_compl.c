/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_compl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:50:31 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/31 15:59:27 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		nbr_perline(int maxlen, int w)
{
	int	i;

	i = 1;
	while (i * maxlen < w)
		i++;
	return ((--i > 0) ? i : 1);
}

int		nbr_percol(int nbrargs, int nbrperline)
{
	int	i;

	i = 1;
	while (i * nbrperline < nbrargs)
		i++;
	return (i);
}

int		maxrow_line(int lenline, int w)
{
	int	i;

	i = 1;
	while (i * w < lenline)
		i++;
	return (i);
}

char	*get_envpath(char ***env)
{
	int		i;

	if (!env || !*env || !**env)
		return (NULL);
	i = -1;
	while ((*env)[++i])
		if (!ft_strncmp("PATH=", (*env)[i], 5))
			return ((*env)[i]);
	return (NULL);
}

int		check_lname(char *n1, char *n2, int len)
{
	if (!n1 || !n2)
		return (0);
	while (len && *n1 && *n2 && ft_toupper(*n1) == ft_toupper(*n2))
	{
		len--;
		n1++;
		n2++;
	}
	if (!len)
		return (0);
	else
		return (*(unsigned char*)n1 - *(unsigned char*)n2);
}
