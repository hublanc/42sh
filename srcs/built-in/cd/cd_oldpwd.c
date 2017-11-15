/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:48:31 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/15 16:21:26 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	change_oldpwd_env_l(char ***env)
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
	check_dotdot(&pwd);
	change_env(env, pwd);
	ft_putendl(pwd);
	ft_strdel(&pwd);
}

int			cd_oldpwd(char ***env, char opt)
{
	t_loc	*loc;
	char	*oldpwd;
	char	pwd[PATH_MAX + 1];

	loc = NULL;
	if (!(oldpwd = get_elem(env, "OLDPWD="))
			&& !(loc = get_loc("OLDPWD")))
	{
		ft_putendl_fd("shell: cd: OLDPWD not set", 2);
		return (1);
	}
	(!oldpwd && loc) ? oldpwd = loc->value : 0;
	if (ft_strlen(oldpwd) > 255 || (opt == 'P' && chdir(oldpwd) == -1)
			|| (oldpwd[0] && chdir(oldpwd) == -1))
		return (error_chdir(&oldpwd, oldpwd, 0));
	if (opt == 'P')
	{
		getcwd(pwd, PATH_MAX);
		change_env(env, pwd);
		ft_putendl(oldpwd);
	}
	else
		change_oldpwd_env_l(env);
	return (0);
}
