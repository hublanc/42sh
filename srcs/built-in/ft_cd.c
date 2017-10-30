/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:02:15 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/30 13:16:22 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_slash(char **content)
{
	if ((*content)[ft_strlen(*content) - 1] != '/')
		*content = ft_strapp(*content, "/");
}

void	change_dir(char *path)
{
	chdir(path);
}

char	*treat_cd_path(char *cdpath, char *arg)
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

char	*treat_without_cdpath(char *arg, char ***env)
{
	char	*curpath;
	char	*pwd;

	if (!(pwd = get_elem(env, "PWD=")))
		if (get_loc("PWD"))
			pwd = get_loc("PWD")->value;
	curpath = ft_strdup(pwd);
	add_slash(&curpath);
	curpath = ft_strapp(curpath, arg);
	return (curpath);
}

void	check_cdopt(char **path, char *opt)
{
	int	i;
	int	ret;

	i = 0;
	while (path[i])
		i++;
	g_optind = 1;
	while ((ret = ft_getopt(i, (const char**)path, "LP")) != -1)
	{
		*opt = ret;
		if (*opt == '?')
			g_optind = -1;
	}
}

void		check_isdotdot(char **tmp)
{
	char	*temp;

	if (ft_strcmp(*tmp, "/"))
	{
		temp = ft_strrchr(*tmp, '/');
		if (!ft_strcmp(temp, *tmp))
			temp[1] = '\0';
		else
			temp[0] = '\0';
	}
}

static void	check_dotdot(char **tmp)
{
	int		i;
	char	**split;

	i = 0;
	if (*tmp && (*tmp)[0] == '/')
	{
		split = ft_strsplit(*tmp, '/');
		ft_strdel(&(*tmp));
		*tmp = ft_strdup("/");
		while (split[i])
		{
			if (!ft_strcmp(split[i], ".."))
				check_isdotdot(tmp);
			else if (ft_strcmp(split[i], "."))
			{
				add_slash(&(*tmp));
				*tmp = ft_strapp(*tmp, split[i]);
			}
			i++;
		}
	}
	del_tabstr(&split);
}

// Check_dotslash is useless I think

/*void	check_dotslash(char **tmp)
{
	int		i;
	char	*new;
	char	*del;

	i = 0;
	while ((*tmp)[i])
	{
		if ((*tmp)[i] == '.' && i > 0 && (*tmp)[i - 1] == '/'
				&& (((*tmp)[i + 1] && (*tmp)[i + 1] == '/') || !((*tmp)[i + 1])))
		{
			new = ft_strsub(*tmp, 0, i - 1);
			del = ft_strsub(*tmp, i + 1, ft_strlen(*tmp));
			new = ft_strapp(new, del);
			ft_strdel(&(*tmp));
			*tmp = new;
			ft_strdel(&del);
		}
		i++;
	}
}*/

void	change_env(char ***env, char *pwd)
{
	char	*oldpwd;
	char	**tmp;

	if (!(oldpwd = get_elem(env, "PWD=")) && get_loc("PWD"))
		oldpwd = get_loc("PWD")->value;
	oldpwd = ft_strdup(oldpwd);
	if (get_elem(env, "PWD=") || get_loc("PWD"))
		add_loc("PWD", pwd);
	else
	{
		tmp = prep_setenv("PWD", pwd);
		ft_setenv(tmp, env);
		del_tabstr(&tmp);
	}
	if (get_elem(env, "OLDPWD=") || get_loc("OLDPWD"))
		add_loc("OLDPWD", oldpwd);
	else
	{
		tmp = prep_setenv("OLDPWD", oldpwd);
		ft_setenv(tmp, env);
		del_tabstr(&tmp);
	}
	ft_strdel(&oldpwd);
}

/*
**	free_pwd is used to know if pwd was malloced (= 1) or not (= 0)
*/

int		error_chdir(char **pwd, char *arg, int free_pwd)
{
	struct stat	s;

	if (lstat(*pwd, &s) != -1 && S_ISDIR(s.st_mode) && !(s.st_mode & S_IXUSR))
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (free_pwd)
		ft_strdel(pwd);
	return (1);
}

int		exec_cd_default(char *curpath, char ***env, char *arg)
{
	char	*pwd;

	// THINK IS USELESS
	/*if (chdir(curpath) == -1)
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}*/
	if (curpath[0] != '/')
	{
		if (!(pwd = get_elem(env, "PWD=")))
			if (get_loc("PWD"))
				pwd = get_loc("PWD")->value;
		pwd = ft_strdup(pwd);
		add_slash(&pwd);
		pwd = ft_strapp(pwd, curpath);
		check_dotdot(&pwd);
	}
	else
		pwd = ft_strdup(curpath);
	if (chdir(pwd) == -1)
		return (error_chdir(&pwd, arg, 1));
	change_env(env, pwd);
	ft_strdel(&pwd);
	return (0);
}

int		exec_cd_p(char *curpath, char ***env, char *arg)
{
	char	pwd[256];

	if (chdir(curpath) == -1)
		return (error_chdir(&curpath, arg, 0));
	getcwd(pwd, 256);
	change_env(env, pwd);
	return (0);
}

void	change_home_env_l(char ***env)
{
	char	*home;
	char	*pwd;

	if (!(home = get_elem(env, "HOME=")) && get_loc("HOME"))
		home = get_loc("HOME")->value;
	if (home[0] == '/')
		pwd = ft_strdup(home);
	else
	{
		if (!(pwd = get_elem(env, "PWD=")) && get_loc("PWD"))
			pwd = get_loc("PWD")->value;
		pwd = ft_strdup(pwd);
		if (pwd && pwd[0])
			add_slash(&pwd);
		pwd = ft_strapp(pwd, home);
	}
	change_env(env, pwd);
	ft_strdel(&pwd);
}

void	change_oldpwd_env_l(char ***env)
{
	char	*oldpwd;
	char	*pwd;

	if (!(oldpwd = get_elem(env, "OLDPWD=")) && get_loc("OLDPWD"))
		oldpwd = get_loc("OLDPWD")->value;
	if (oldpwd[0] == '/')
		pwd = ft_strdup(oldpwd);
	else
	{
		if (!(pwd = get_elem(env, "PWD=")) && get_loc("PWD"))
			pwd = get_loc("PWD")->value;
		pwd = ft_strdup(pwd);
		if (pwd && pwd[0])
			add_slash(&pwd);
		pwd = ft_strapp(pwd, oldpwd);
	}
	change_env(env, pwd);
	ft_strdel(&pwd);
}

int		cd_home(char ***env, char opt)
{
	t_loc	*loc;
	char	*home;
	char	pwd[256];

	loc = NULL;
	if (!(home = get_elem(env, "HOME="))
			&& !(loc = get_loc("HOME")))
	{
		ft_putendl_fd("42sh: cd: HOME not set", 2);
		return (1);
	}
	(!home && loc) ? home = loc->value : 0;
	if ((opt == 'P' && chdir(home) == -1)
			|| (home[0] && chdir(home) == -1))
		return (error_chdir(&home, home, 0));
	if (opt == 'P')
	{
		getcwd(pwd, 256);
		change_env(env, pwd);
	}
	else
		change_home_env_l(env);
	return (0);
}

int		cd_oldpwd(char ***env, char opt)
{
	t_loc	*loc;
	char	*oldpwd;
	char	pwd[256];

	loc = NULL;
	if (!(oldpwd = get_elem(env, "OLDPWD="))
			&& !(loc = get_loc("OLDPWD")))
	{
		ft_putendl_fd("42sh: cd: OLDPWD not set", 2);
		return (1);
	}
	(!oldpwd && loc) ? oldpwd = loc->value : 0;
	if ((opt == 'P' && chdir(oldpwd) == -1)
			|| (oldpwd[0] && chdir(oldpwd) == -1))
		return (error_chdir(&oldpwd, oldpwd, 0));
	ft_putendl(oldpwd);
	if (opt == 'P')
	{
		getcwd(pwd, 256);
		change_env(env, pwd);
	}
	else
		change_oldpwd_env_l(env);
	return (0);
}

int		exec_cd_default_cdpath(char **curpath, char ***env, char *arg)
{
	char	*pwd;

	if (arg[0] != '/')
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
	if (!(*curpath) || chdir(pwd) == -1)
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

int		exec_cd_p_cdpath(char **curpath, char ***env, char *arg)
{
	char	pwd[256];

	if (!(*curpath) || chdir(*curpath) == -1)
		return (error_chdir(curpath, arg, 1));
	ft_strdel(curpath);
	ft_putendl(arg);
	getcwd(pwd, 256);
	change_env(env, pwd);
	return (0);
}

int		cd_treat_path(char *path, char opt, char ***env, char *arg)
{
	if (opt == 'P')
		return (exec_cd_p(path, env, arg));
	else
		return (exec_cd_default(path, env, arg));
}

int		cd_treat_path_cdpath(char **path, char opt, char ***env, char *arg)
{
	if (opt == 'P')
		return (exec_cd_p_cdpath(path, env, arg));
	else
		return (exec_cd_default_cdpath(path, env, arg));
}

int		cd_exec(char ***env, char **tab, char opt)
{
	char	*curpath;
	char	*cdpath;

	curpath = NULL;
	if (tab[g_optind] && tab[g_optind][0] == '/')
		return (cd_treat_path(tab[g_optind], opt, env, tab[g_optind]));
	else if (tab[g_optind] && tab[g_optind][0] == '.')
		return (cd_treat_path(tab[g_optind], opt, env, tab[g_optind]));
	else if (tab[g_optind] && ((cdpath = get_elem(env, "CDPATH="))
			|| (get_loc("CDPATH") && (cdpath = get_loc("CDPATH")->value))))
	{
		curpath = treat_cd_path(cdpath, tab[g_optind]);
		return (cd_treat_path_cdpath(&curpath, opt, env, tab[g_optind]));
	}
	else if (tab[g_optind])
		return (cd_treat_path(tab[g_optind], opt, env, tab[g_optind]));
	return (1);
}

int		ft_cd(char **tab, char ***env)
{
	char	opt;

	opt = 'L';
	check_cdopt(tab, &opt);
	if (g_optind == -1)
		return (1);
	if (!tab[g_optind])
		return (cd_home(env, opt));
	else if (tab[g_optind] && !ft_strcmp(tab[g_optind], "-"))
		return (cd_oldpwd(env, opt));
	else
		return (cd_exec(env, tab, opt));
	return (0);
}
