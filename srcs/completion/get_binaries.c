/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:18:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 16:38:23 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	get_files(t_compl *compl, DIR *dirp, t_coargs **args, int idcount)
{
	struct dirent	*dirc;
	t_coargs		*tmp;

	if (!(dirc = readdir(dirp)))
		return (0);
	tmp = *args;
	if (compl->arg && ft_strncmp(dirc->d_name, compl->arg, ft_strlen(compl->arg)))
	{
		if (get_files(compl, dirp, args, ++idcount) == 0)
		{
			free(tmp->next);
			tmp->next = NULL;
		}
		return (1);
	}
	(*args)->id = idcount;
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
	if (get_files(compl, dirp, args, ++idcount) == 0)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
	return (1);
}

void	get_args(t_compl *compl, char **paths)
{
	t_coargs *complarg;
	DIR		*dirp;
	int		i;

	if (compl || paths)
		;
	complarg = &compl->args;
	i = -1;
	while (paths[++i])
	{
		if (check_access(paths[i]) && (dirp = opendir(paths[i])))
		{
			get_files(compl, dirp, &complarg, 0);
			closedir(dirp);
		}
	}
}
