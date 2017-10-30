/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:43:04 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/30 17:08:53 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	change_home_env_l(char ***env)
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

int			cd_home(char ***env, char opt)
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
