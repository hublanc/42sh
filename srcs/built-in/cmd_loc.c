/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:46:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/05 15:10:23 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_afterequal(char *cmmd, int i)
{
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
		cmmd[i] ? i++ : 0;
	}
	return (i);
}

static int	endloc(char *cmmd)
{
	int	i;

	i = 0;
	if (!cmmd[i])
		return (0);
	while (cmmd[i] == 32 || cmmd[i] == 9 || cmmd[i] == '\n')
		i++;
	while (cmmd[i] && cmmd[i + 1] && cmmd[i] == '\\')
		i += 2;
	while (cmmd && cmmd[i] && (ft_isalpha(cmmd[i]) || ft_isalnum(cmmd[i])
			|| cmmd[i] == '_'))
	{
		if (cmmd[i] == '\'' || (i > 0 && (cmmd[i] == '"' || cmmd[i] == 32)))
			return (0);
		while (cmmd[i] && cmmd[i + 1] && cmmd[i] == '\\')
		{
			i += 2;
			if (!cmmd[i - 2] || cmmd[i - 1] || cmmd[i])
				return (0);
		}
		i++;
	}
	if (!cmmd[i])
		return (0);
	return (i);
}

static int	check_cmmd(char **cmmd)
{
	char	*s;
	int		i;

	if (!(i = endloc(*cmmd)))
		return (0);
	if (i == 0 || (*cmmd)[i] != '=')
		return (0);
	s = NULL;
	if (!(i = check_afterequal(*cmmd, i)))
		s = ((*cmmd)[i]) ? ft_strdup(*cmmd + i) : NULL;
	if ((*cmmd)[i] == 32)
	{
		free(*cmmd);
		*cmmd = s;
		return (0);
	}
	return (1);
}

int			gest_loc(char **cmmd)
{
	char	**tab;
	int		i;

	if (!(check_cmmd(cmmd)))
		return (0);
	if (!(tab = ft_strsplit(*cmmd, '=')) || !tab || !tab[0])
	{
		tab ? free(tab) : 0;
		return (0);
	}
	i = -1;
	while (tab[1] && tab[1][++i])
		if (tab[1][i] == '"' && (i < 1 || tab[1][i - 1] != '\\'))
			ssupprchr(&tab[1], i--);
	add_loc(tab[0], tab[1]);
	reset_status();
	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
	free(tab);
	return (1);
}
