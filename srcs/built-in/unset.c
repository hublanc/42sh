/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:40:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 18:17:34 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	argunset(char *name, char ***env)
{
	char	**tab;
	int		i;

	if (!get_loc(name) && env && *env)
	{
		i = 0;
		while ((*env)[i] && ft_strncmp((*env)[i], name,
					ft_strlen_chr((*env)[i], '=') - 1))
			i++;
		if (!(*env)[i] || ft_strcmp((*env)[i], name))
			return (1);
		else
		{
			if (!(tab = (char **)ft_memalloc(sizeof(char *) * 3)))
				return (1);
			tab[0] = "unsetenv";
			tab[1] = name;
			tab[2] = NULL;
			i = ft_unsetenv(tab, env);
			free(tab);
			return (i);
		}
	}
	return (0);
}

int			unset(char **tab, char ***env)
{
	int	i;
	int	status;

	if (tab[0] && !tab[1])
		return (0);
	i = 0;
	status = 0;
	while (tab[++i])
		if (argunset(tab[i], env))
			status = 1;
	return (status);
}
