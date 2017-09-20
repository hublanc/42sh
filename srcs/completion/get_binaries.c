/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:18:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 13:32:40 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_files(t_compl *compl, DIR *dirp, t_coargs **args, int *idcount)
{
	struct dirent	*dirc;
	t_coargs		*tmp;

	if (!(dirc = readdir(dirp)))
		return (1);
	tmp = *args;
	if (compl->arg && ft_strncmp(dirc->d_name, compl->arg, ft_strlen(compl->arg)))
		return (get_files(compl, dirp, args, idcount));
	(*args)->id = (*idcount)++;
	(*args)->arg = ft_strdup(dirc->d_name);
	compl->nbrargs++;
	if (ft_strlen((*args)->arg) + 1 > compl->maxlen)
		compl->maxlen = ft_strlen((*args)->arg) + 1;
	if (!((*args)->next = (t_coargs *)ft_memalloc(sizeof(t_coargs))))
	{
		(*args)->next = NULL;
		return (-1);
	}
	(*args) = (*args)->next;
	(*args)->arg = NULL;
	return (get_files(compl, dirp, args, idcount) == 0);
	return (1);
}

void	get_args(t_compl *compl, char **paths)
{
	t_coargs *complarg;
	DIR		*dirp;
	int		id;
	int		i;

	if (compl || paths)
		;
	complarg = &compl->args;
	id = 0;
	i = -1;
	while (paths[++i])
	{
		if (check_access(paths[i]) && (dirp = opendir(paths[i])))
		{
			get_files(compl, dirp, &complarg, &id);
			closedir(dirp);
		}
	}
}
