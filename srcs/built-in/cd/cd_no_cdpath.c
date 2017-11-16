/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_no_cdpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:56:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 10:34:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*treat_without_cdpath(char *arg, char ***env)
{
	char	*curpath;
	char	*pwd;

	if (!(pwd = get_elem(env, "PWD=")))
		if (get_loc("PWD"))
			pwd = get_loc("PWD")->value;
	if (!pwd)
	{
		curpath = ft_strnew(PATH_MAX);
		getcwd(curpath, PATH_MAX + 1);
	}
	else
		curpath = ft_strdup(pwd);
	add_slash(&curpath);
	curpath = ft_strapp(curpath, arg);
	return (curpath);
}

static int	exec_cd_default(char *curpath, char ***env, char *arg)
{
	char	*pwd;

	if (curpath[0] != '/')
	{
		if (!(pwd = get_elem(env, "PWD=")))
			if (get_loc("PWD"))
				pwd = get_loc("PWD")->value;
		if (!pwd)
		{
			pwd = ft_strnew(PATH_MAX + 1);
			getcwd(pwd, PATH_MAX);
		}
		else
			pwd = ft_strdup(pwd);
		add_slash(&pwd);
		pwd = ft_strapp(pwd, curpath);
		check_dotdot(&pwd);
	}
	else
		pwd = ft_strdup(curpath);
	if (ft_strlen(arg) > 255 || chdir(pwd) == -1)
		return (error_chdir(&pwd, arg, 1));
	change_env(env, pwd);
	ft_strdel(&pwd);
	return (0);
}

static int	exec_cd_p(char *curpath, char ***env, char *arg)
{
	char	pwd[PATH_MAX + 1];

	if (ft_strlen(arg) > 255 || chdir(curpath) == -1)
		return (error_chdir(&curpath, arg, 0));
	getcwd(pwd, PATH_MAX);
	change_env(env, pwd);
	return (0);
}

int			cd_treat_path(char *path, char opt, char ***env, char *arg)
{
	if (opt == 'P')
		return (exec_cd_p(path, env, arg));
	else
		return (exec_cd_default(path, env, arg));
}
