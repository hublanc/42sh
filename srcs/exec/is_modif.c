/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_modif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 15:27:58 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/09 15:46:52 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**singleton_path(char *path)
{
	static char		*s_path = NULL;

	if (!path)
		return (&s_path);
	else
	{
		if (s_path)
			ft_strdel(&s_path);
		s_path = ft_strdup(path);
		return (&s_path);
	}
}

void		load_path(char **env)
{
	int		pos;

	if (!env || !*env)
		return ;
	if ((pos = in_env("PATH", env)) != -1)
		singleton_path(env[pos]);
}

void		is_modif(char **env)
{
	t_hash	**hash;
	char	**path;
	int		pos;

	if (!env || !*env)
		return ;
	path = singleton_path(NULL);
	hash = singleton_hash();
	if (path && *path && (pos = in_env("PATH", env)) != -1)
	{
		if (ft_strcmp(env[pos], *path))
			del_hash(hash);
	}
	else
		del_hash(hash);
}

void		del_spath(void)
{
	char		**path;

	path = singleton_path(NULL);
	if (path && *path)
		ft_strdel(&(*path));
}
