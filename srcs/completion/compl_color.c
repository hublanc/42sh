/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:29:13 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/27 13:28:56 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	file_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	if (mode & S_IXUSR)
		return ('e');
	if (S_ISREG(mode))
		return ('-');
	return ('?');
}

static char	*compl_color(char *av)
{
	struct stat	atr;

	if (lstat(av, &atr) == -1)
		return (NULL);
	if (file_type(atr.st_mode) == 'd')
		return ("\e[1;36m");
	if (file_type(atr.st_mode) == 'l')
		return ("\e[35m");
	if (file_type(atr.st_mode) == 'e')
		return ("\e[31m");
	return ("\e[39m");
}

void		compl_addcolor(t_coargs **ar, char *path)
{
	char *tmp;
	char *tmp2;

	if (*ar && (*ar)->arg)
	{
		if (!path)
			path = ".";
		if (!(tmp = ft_strjoin(path, "/")))
		{
			(*ar)->color = NULL;
			return ;
		}
		if (!(tmp2 = ft_strjoin(tmp, (*ar)->arg)))
		{
			free(tmp);
			(*ar)->color = NULL;
			return ;
		}
		(*ar)->color = compl_color(tmp2);
		free(tmp);
		free(tmp2);
	}
	else
		(*ar)->color = NULL;
}
