/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:18:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/31 11:13:54 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_arg(t_compl *compl, struct dirent *dirc, t_coargs **args)
{
	char			*t;

	(*args)->arg = add_handspace(dirc->d_name);
	compl_addcolor(args, compl->path);
	if ((*args)->color && !ft_strcmp("\e[1;36m", (*args)->color))
	{
		if ((t = ft_strjoin((*args)->arg, "/")))
		{
			((*args)->arg) ? free((*args)->arg) : 0;
			(*args)->arg = ft_strdup(t);
			free(t);
		}
	}
	compl->nbrargs++;
	if (ft_strlen((*args)->arg) + 1 > compl->maxlen)
		compl->maxlen = ft_strlen((*args)->arg) + 1;
}

int			get_files(t_compl *compl, DIR *dirp, t_coargs **args, int *idcount)
{
	struct dirent	*dirc;

	if (!(dirc = readdir(dirp)))
		return (1);
	if ((compl->arg && check_lname(compl->arg, dirc->d_name,
		ft_strlen(compl->arg))) || (dirc->d_name[0] == '.'
		&& (!compl->isdot || (dirc->d_name[1] && dirc->d_name[1] == '.'))))
		return (get_files(compl, dirp, args, idcount));
	add_arg(compl, dirc, args);
	(*args)->id = (*idcount)++;
	if (!((*args)->next = (t_coargs *)ft_memalloc(sizeof(t_coargs))))
	{
		(*args)->next = NULL;
		return (-1);
	}
	(*args) = (*args)->next;
	(*args)->arg = NULL;
	(*args)->next = NULL;
	return (get_files(compl, dirp, args, idcount) == 0);
}

int		new_complarg(t_coargs **args)
{
	int	id;

	if (*args && (*args)->arg)
	{
		while ((*args)->next && (*args)->next->arg)
			*args = (*args)->next;
		if ((*args)->next)
			free((*args)->next);
		if (!((*args)->next = (t_coargs *)ft_memalloc(sizeof(t_coargs))))
		{
			(*args)->next = NULL;
			return (-1);
		}
		id = (*args)->id + 1;
		(*args) = (*args)->next;
		(*args)->arg = NULL;
		(*args)->next = NULL;
		return (id);
	}
	return (0);
}

void		get_args(t_compl *compl, char **paths)
{
	t_coargs	*args;
	DIR			*dirp;
	int			id;
	int			i;

	args = &compl->args;
	i = -1;
	if ((id = new_complarg(&args)) == -1)
		return ;
	while (paths[++i])
	{
		if (check_access(paths[i]) && (dirp = opendir(paths[i])))
		{
			get_files(compl, dirp, &args, &id);
			closedir(dirp);
		}
	}
	get_locenv(compl);
}
