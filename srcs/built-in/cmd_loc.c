/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:46:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/05 16:55:23 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		endloc(char *cmmd)
{
	int	i;

	i = 0;
	if (!cmmd[i])
		return (0);
	while (cmmd[i] == 32 || cmmd[i] == 9 || cmmd[i] == '\n')
		i++;
	while (cmmd[i] && cmmd[i + 1] && cmmd[i] == '\\')
		i += 2;
	while (cmmd[i] && cmmd[i] != '=')
	{
		if (cmmd[i] == '\'' || cmmd[i] == '"')
			return (0);
		while (cmmd[i] && cmmd[i + 1] && cmmd[i] == '\\')
			i += 2;
		i++;
	}
	if (!cmmd[i])
		return (0);
	while (cmmd[i] && cmmd[i] != 32)
	{
		if (cmmd[i] == '\'')
		{
			i++;
			while (cmmd[i] && cmmd[i] != '\'')
				i++;
		}
		else if (cmmd[i] == '"')
		{
			i++;
			while (cmmd[i] && cmmd[i] != '"')
				i++;
		}
		while (cmmd[i] && cmmd[i + 1] && cmmd[i] == '\\')
			i += 2;
		i++;
	}
	return (i);
}

int		gest_loc(char **cmmd)
{
	char	**tab;
	char	*s;
	int		i;

	if (!(i = endloc(*cmmd)))
		return (0);;
	s = ((*cmmd)[i]) ? ft_strdup(*cmmd + i) : NULL;
	if ((*cmmd)[i] == 32)
	{
		free(*cmmd);
		*cmmd = s;
		return (0);
	}
	tab = ft_strsplit(*cmmd, '=');
	add_loc(tab[0], tab[1]);
	free(tab[1]);
	free(tab[0]);
	free(tab);
	return (1);
}
