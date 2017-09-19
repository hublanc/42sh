/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:48:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 16:38:46 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_path(char ***env)
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

void		list_compl(t_compl *compl, char ***env)
{
	char	*path;
	char	**paths;

	paths = NULL;
	compl->args.next = NULL;
	compl->maxlen = 0;
	compl->nbrargs = 0;
	if ((path = get_path(env)))
		paths = ft_strsplit(path + 5, ':');
	if (paths && paths[0])
		get_args(compl, paths);
}
