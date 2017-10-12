/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:46:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 11:56:18 by amazurie         ###   ########.fr       */
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
		if (cmmd[i] == '\'' || (i > 0 && (cmmd[i] == '"' || cmmd[i] == 32)))
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

static void	ssupprchr(char **s, int pos)
{
	int i;

	pos--;
	i = ft_strlen(*	s) - 1;
	while (++pos <= i)
		(*s)[pos] = (*s)[pos + 1];
}

int		gest_loc(char **cmmd, char ***env)
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
	i = -1;
	while (tab[1] && tab[1][++i])
		if (tab[1][i] == '"' && (i < 1 || tab[1][i - 1] != '\\'))
			ssupprchr(&tab[1], i--);
	add_loc(tab[0], tab[1], env);
	free(tab[1]);
	free(tab[0]);
	free(tab);
	return (1);
}
