/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:01:43 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 16:48:51 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		change_pwd(char ***env)
{
	char	*old;
	char	*new;
	int		pos;
	char	**save;
	char	**tab;

	pos = in_env("PWD", *env);
	if (pos == -1)
		pos = pwdnotset(env);
	save = *env;
	while (pos--)
		(*env)++;
	old = ft_strsub(**env, 4, ft_strlen(**env) - 4);
	*env = save;
	new = getcwd(NULL, PATH_MAX + 1);
	tab = prep_setenv("OLDPWD", old);
	ft_setenv(tab, env);
	del_tabstr(&tab);
	tab = prep_setenv("PWD", new);
	ft_setenv(tab, env);
	del_tabstr(&tab);
	ft_strdel(&old);
	ft_strdel(&new);
}

int			cd_home(char ***env)
{
	char		*new;
	int			pos;
	char		**save;
	int			perm;

	pos = in_env("HOME", *env);
	if (pos == -1)
		return (print_error(3, NULL));
	save = *env;
	while (pos--)
		(*env)++;
	new = ft_strsub(**env, 5, ft_strlen(**env) - 5);
	*env = save;
	if ((perm = check_access(new)) < 0)
	{
		print_error(perm == -1 ? 1 : 4, new);
		ft_strdel(&new);
		return (1);
	}
	chdir(new);
	change_pwd(env);
	ft_strdel(&new);
	return (0);
}

int			cd_prev(char ***env)
{
	int		pos;
	int		perm;
	char	*new;
	char	**save;

	pos = in_env("OLDPWD", *env);
	if (pos == -1)
		return (print_error(6, NULL));
	save = *env;
	while (pos--)
		(*env)++;
	new = ft_strsub(**env, 7, ft_strlen(**env) - 7);
	*env = save;
	if ((perm = check_access(new)) < 0)
	{
		print_error(perm == -1 ? 1 : 4, new);
		ft_strdel(&new);
		return (1);
	}
	chdir(new);
	change_pwd(env);
	ft_strdel(&new);
	return (0);
}

int			ft_cd(char **tab, char ***env)
{
	int			len;
	int			perm;

	len = len_array(tab);
	if (len == 1 || (tab[1] && ft_strcmp(tab[1], "~") == 0))
		return (cd_home(env));
	else if (tab[1] && ft_strcmp(tab[1], "-") == 0)
		return (cd_prev(env));
	else if (len == 2)
	{
		if ((perm = check_access(tab[1])) < 0)
			return (print_error(perm == -1 ? 1 : 4, tab[1]));
		chdir(tab[1]);
		change_pwd(env);
		return (0);
	}
	else
	{
		ft_putstr_fd("string not in pwd: ", 2);
		ft_putstr_fd(tab[1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
}
