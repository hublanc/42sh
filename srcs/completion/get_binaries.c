/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:18:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 12:57:38 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	get_files(t_compl *compl, DIR *dirp, char *arg)
{
	struct dirent	*dirc;

	if (!(dirc = readdir(dirp)))
		return ;
	if (arg && ft_strncmp(dirc->d_name, arg, ft_strlen(arg)))
	{
		get_files(compl, dirp, arg);
		return ;
	}
	compl->arg = ft_strdup(dirc->d_name);
	if (!(compl->next = (t_compl *)ft_memalloc(sizeof(t_compl))))
	{
		compl->next = NULL;
		return ;
	}
	compl = compl->next;
	get_files(compl, dirp, arg);
}

void	get_args(t_compl *compl, char **paths, char *arg)
{
	t_compl *compltmp;
	DIR		*dirp;
	int		i;

	if (compl || paths || arg)
		;
	compltmp = compl;
	i = -1;
	while (paths[++i])
	{
//		if (check_access())
		if ((dirp = opendir(paths[i])))
			get_files(compltmp, dirp, arg);
	}
}
