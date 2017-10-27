/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:02:15 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/27 15:09:16 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_slash(char **content)
{
	if ((*content)[ft_strlen(*content)] != '/')
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
	path = NULL;
	while (split_cdpath && split_cdpath[i])
	{
		add_slash(&split_cdpath[i]);
		split_cdpath[i] = ft_strapp(split_cdpath[i], arg);
		if (lstat(split_cdpath[i], &s) != -1)
		{
			if (s.st_mode == S_IFDIR)
			{
				path = ft_strdup(split_cdpath[i]);
				//FREE SPLIT
				return (path);
			}
		}
		i++;
	}
	//MAYBE PRINT ERROR
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

static void	check_dotdot(char **tmp)
{
	size_t	i;

	if (!*tmp)
		return ;
	while ((i = ft_strschr_len(*tmp, "..")))
	{
		while (i == ft_strschr_len(*tmp + i, "..."))
		{
			while ((*tmp)[i] == '.')
				i++;
			if (!ft_strschr_len(*tmp + i, ".."))
				return ;
		}
		while ((*tmp)[i] && (*tmp)[i] != '/')
			ssupprchr(tmp, i);
		ssupprchr(tmp, i--);
		ssupprchr(tmp, i--);
		if (ft_strschr_len(*tmp, "/") <= i)
			while ((*tmp)[i] && (*tmp)[i] != '/')
				ssupprchr(tmp, i--);
	}
	(*tmp)[ft_strlen(*tmp) - 1] == '/' ? (*tmp)[ft_strlen(*tmp) - 1] = 0 : 0;
	if (!(*tmp)[0])
		(*tmp)[0] = '/';
}

void	check_dotslash(char **tmp)
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
			printf("ON ENTRE\n");
			new = ft_strsub(*tmp, 0, i - 1);
			del = ft_strsub(*tmp, i + 1, ft_strlen(*tmp));
			new = ft_strapp(new, del);
			ft_strdel(&(*tmp));
			*tmp = new;
			ft_strdel(&del);
		}
		i++;
	}
}

int		exec_cd_default(char *curpath, char ***env)
{
	char	*pwd;
	char	*oldpwd;
	char	**tab_setenv;

	if (chdir(curpath) == -1)
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(curpath, 2);
		return (1);
	}
	if (!(pwd = get_elem(env, "PWD=")))
		if (get_loc("PWD"))
			pwd = get_loc("PWD")->value;
	pwd = ft_strdup(pwd);
	add_slash(&pwd);
	pwd = ft_strapp(pwd, curpath);
	check_dotdot(&pwd);
	check_dotslash(&pwd);
	if (!(oldpwd = get_elem(env, "PWD=")))
		if (get_loc("PWD"))
			oldpwd = get_loc("PWD")->value;
	if (oldpwd)
		add_loc("OLDPWD", oldpwd);
	if (!get_elem(env, "PWD=") && get_loc("PWD"))
	{
		add_loc("PWD", pwd);
	}
	else
	{
		tab_setenv = prep_setenv("PWD", pwd);
		ft_setenv(tab_setenv, env);
		//FREE TAB
	}
	ft_strdel(&pwd);
	return (0);
}

int		exec_cd_P(char *curpath, char ***env)
{
	char	*oldpwd;
	char	pwd[256];

	if (chdir(curpath) == -1)
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(curpath, 2);
		return (1);
	}
	if (!(oldpwd = get_elem(env, "PWD=")))
		if (get_loc("PWD"))
			oldpwd = get_loc("PWD")->value;
	if (oldpwd)
		add_loc("OLDPWD", oldpwd);
	getcwd(pwd, 256);
	add_loc("PWD", pwd);
	return (0);
}

void	change_env(char ***env, char *pwd)
{
	char	*oldpwd;
	char	**tmp;

	//printf("APRES pwd = [%s]\n", pwd);
	if (!(oldpwd = get_elem(env, "PWD=")) && get_loc("PWD"))
		oldpwd = get_loc("PWD")->value;
	oldpwd = ft_strdup(oldpwd);
	if (get_elem(env, "PWD=") || get_loc("PWD"))
		add_loc("PWD", pwd);
	else
	{
		tmp = prep_setenv("PWD", pwd);
		ft_setenv(tmp, env);
		//FREE tmp
	}
	if (get_elem(env, "OLDPWD=") || get_loc("OLDPWD"))
		add_loc("OLDPWD", oldpwd);
	else
	{
		tmp = prep_setenv("OLDPWD", oldpwd);
		ft_setenv(tmp, env);
		//FREE tmp
	}
	ft_strdel(&oldpwd);
}

void	change_home_env_L(char ***env)
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

void	change_oldpwd_env_L(char ***env)
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
	if (!(home = get_elem(env, "HOME=")) && !(loc = get_loc("HOME")))
	{
		ft_putendl_fd("42sh: cd: HOME not set", 2);
		return (1);
	}
	(!home && loc) ? home = loc->value : 0;
	if ((opt == 'P' && chdir(home) == -1)
			|| (home[0] && chdir(home) == -1))
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	if (opt == 'P')
	{
		getcwd(pwd, 256);
		change_env(env, pwd);
	}
	else
		change_home_env_L(env);
	return (0);
}

int		cd_oldpwd(char ***env, char opt)
{
	t_loc	*loc;
	char	*oldpwd;
	char	pwd[256];

	loc = NULL;
	if (!(oldpwd = get_elem(env, "OLDPWD=")) && !(loc = get_loc("OLDPWD")))
	{
		ft_putendl_fd("42sh: cd: OLDPWD not set", 2);
		return (1);
	}
	(!oldpwd && loc) ? oldpwd = loc->value : 0;
	if ((opt == 'P' && chdir(oldpwd) == -1)
			|| (oldpwd[0] && chdir(oldpwd) == -1))
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(oldpwd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	ft_putendl(oldpwd);
	if (opt == 'P')
	{
		getcwd(pwd, 256);
		change_env(env, pwd);
	}
	else
		change_oldpwd_env_L(env);
	return (0);
}

int		ft_cd(char **tab, char ***env)
{
	/*char	*home;
	char	*curpath;
	char	*cdpath;*/
	char	opt;

	opt = 'L';
	check_cdopt(tab, &opt);
	//curpath = NULL;
	if (g_optind == -1)
		return (1);
	if (!tab[g_optind])
		return (cd_home(env, opt));
	else if (tab[g_optind] && !ft_strcmp(tab[g_optind],"-"))
		return (cd_oldpwd(env, opt));
	/*
	if (!tab[g_optind] && !get_elem(env, "HOME=") && !get_loc("HOME"))
	{
		ft_putendl_fd("42sh: cd: HOME not set", 2);
		return (1);
	}
	else if (!tab[g_optind] && ((home = get_elem(env, "HOME="))
				|| (get_loc("HOME")
					&& (home = get_loc("HOME")->value))) && home[0])
		curpath = ft_strdup(home);
	else if (tab[g_optind] && tab[g_optind][0] == '-')
		cd_oldpath(env);
	else if (tab[g_optind] && tab[g_optind][0] == '/')
	{
		if (opt == 'P')
			return (exec_cd_P(tab[g_optind], env));
		else
			return (exec_cd_default(tab[g_optind], env));
	}
	else if (tab[g_optind] && tab[g_optind][0] == '.')
		curpath = ft_strdup(tab[g_optind]);
	else if (tab[g_optind] && ((cdpath = get_elem(env, "CDPATH="))
			|| (get_loc("CDPATH") && (cdpath = get_loc("CDPATH")->value))))
		curpath = treat_cd_path(cdpath, tab[g_optind]);
	else if (tab[g_optind])
		curpath = treat_without_cdpath(tab[g_optind], env);
	if (opt == 'P' && curpath)
		return (exec_cd_P(curpath, env));
	else if (curpath)
		return (exec_cd_default(curpath, env));
		*/
	return (0);
}
