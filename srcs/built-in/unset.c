/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:40:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/26 17:18:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	argunset(char *name, char ***env)
{
	char	**new;
	int		i;

	if ((i = 0) == 0 && get_loc(name) && env && *env)
	{
		suppr_loc(name);
		return (0);
	}
	while ((*env)[i] && ft_strncmp((*env)[i], name,
				ft_strlen_chr((*env)[i], '=') - 1))
		i++;
	if (!(*env)[i] || ft_strncmp((*env)[i], name,
				ft_strlen_chr((*env)[i], '=') - 1))
		return (1);
	new = delonenv(name, *env);
	del_tabstr(env);
	*env = new;
	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], name,
				ft_strlen_chr((*env)[i], '=') - 1))
		i++;
	if (!(*env)[i] || ft_strncmp((*env)[i], name,
				ft_strlen_chr((*env)[i], '=') - 1))
		return (0);
	return (1);
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
