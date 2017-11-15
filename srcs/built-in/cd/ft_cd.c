/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:02:15 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/15 16:00:43 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		add_slash(char **content)
{
	if ((*content)[ft_strlen(*content) - 1] != '/')
		*content = ft_strapp(*content, "/");
}

static void	check_cdopt(char **path, char *opt)
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
			return ;
	}
}

void		change_env(char ***env, char *pwd)
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

static int	cd_exec(char ***env, char **tab, char opt)
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

int			ft_cd(char **tab, char ***env)
{
	char	opt;

	opt = 'L';
	check_cdopt(tab, &opt);
	if (g_optind == -1 || (opt != 'L' && opt != 'P'))
		return (1);
	if (!tab[g_optind])
		return (cd_home(env, opt));
	else if (tab[g_optind] && !ft_strcmp(tab[g_optind], "-"))
		return (cd_oldpwd(env, opt));
	else
		return (cd_exec(env, tab, opt));
	return (0);
}
