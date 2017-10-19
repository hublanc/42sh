/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:40:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/19 15:30:56 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	argunset(char *name, char ***env)
{
	int		i;

	if (!get_loc(name) && env && *env)
	{
		i = 0;
		while ((*env)[i] && ft_strncmp((*env)[i], name,
					ft_strlen_chr((*env)[i], '=') - 1))
			i++;
		if (!(*env)[i] || ft_strncmp((*env)[i], name,
					ft_strlen_chr((*env)[i], '=') - 1))
			return (1);
		else
		{
			*env = delonenv(name, *env);
			i = 0;
			while ((*env)[i] && ft_strncmp((*env)[i], name,
					ft_strlen_chr((*env)[i], '=') - 1))
				i++;
			if (!(*env)[i] || ft_strncmp((*env)[i], name,
					ft_strlen_chr((*env)[i], '=') - 1))
				return (0);
			return (1);
		}
	}
	suppr_loc(name);
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
