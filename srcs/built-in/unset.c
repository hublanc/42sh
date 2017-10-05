/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:40:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/05 17:06:32 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	argunset(char *name, char ***env)
{
	char	**tab;
	int		i;

	if (!get_loc(name))
	{
		i = 0;
		while ((*env)[i] && ft_strncmp((*env)[i], name,
					ft_strlen_chr((*env)[i], '=') - 1))
			i++;
		if (!(*env)[i] || ft_strcmp((*env)[i], name))
				return (0);
		else
		{
			if(!(tab = (char **)ft_memalloc(sizeof (char *) * 3)))
					return (0);
			tab[0] = "unsetenv";
			tab[1] = name;
			tab[2] = NULL;
			ft_unsetenv(tab, env);
			free(tab);
		}
	}
	return (1);
}

int			unset(char **tab, char ***env)
{
	int	i;
	int	j;

	if (tab[0] && !tab[1])
		ft_putstr_fd("unset: not enough arguments", 2);
	i = 0;
	j = 1;
	while (tab[++i])
		j = argunset(tab[i], env);
	return (j);
}
