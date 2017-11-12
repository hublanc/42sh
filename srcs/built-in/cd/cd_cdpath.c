/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cdpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:52:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/12 14:08:32 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*treat_cd_path(char *cdpath, char *arg)
{
	char		**split_cdpath;
	struct stat	s;
	int			i;
	char		*path;

	i = 0;
	split_cdpath = ft_strsplit(cdpath, ':');
	while (split_cdpath && split_cdpath[i])
	{
		add_slash(&split_cdpath[i]);
		split_cdpath[i] = ft_strapp(split_cdpath[i], arg);
		if (lstat(split_cdpath[i], &s) != -1)
		{
			if (S_ISDIR(s.st_mode))
			{
				path = ft_strdup(split_cdpath[i]);
				del_tabstr(&split_cdpath);
				return (path);
			}
		}
		i++;
	}
	del_tabstr(&split_cdpath);
	return (NULL);
}

static int	exec_cd_default_cdpath(char **curpath, char ***env, char *arg)
{
	char	*pwd;

	if (*curpath && (*curpath)[0] != '/')
	{
		if (!(pwd = get_elem(env, "PWD=")))
			if (get_loc("PWD"))
				pwd = get_loc("PWD")->value;
		pwd = ft_strdup(pwd);
		add_slash(&pwd);
		pwd = ft_strapp(pwd, *curpath);
		check_dotdot(&pwd);
	}
	else
		pwd = ft_strdup(*curpath);
	if (!(*curpath) || ft_strlen(arg) > 255 || chdir(pwd) == -1)
	{
		ft_strdel(curpath);
		return (error_chdir(&pwd, arg, 1));
	}
	ft_strdel(curpath);
	ft_putendl(pwd);
	change_env(env, pwd);
	ft_strdel(&pwd);
	return (0);
}

static int	exec_cd_p_cdpath(char **curpath, char ***env, char *arg)
{
	char	pwd[PATH_MAX + 1];

	if (!(*curpath) || ft_strlen(arg) > 255 || chdir(*curpath) == -1)
		return (error_chdir(curpath, arg, 1));
	ft_strdel(curpath);
	ft_putendl(arg);
	getcwd(pwd, PATH_MAX);
	change_env(env, pwd);
	return (0);
}

int			cd_treat_path_cdpath(char **path, char opt, char ***env, char *arg)
{
	if (opt == 'P')
		return (exec_cd_p_cdpath(path, env, arg));
	else
		return (exec_cd_default_cdpath(path, env, arg));
}
