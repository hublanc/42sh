/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 12:01:43 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/06 18:18:53 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**prep_setenv(char *name, char *value)
{
	char		**tab;

	tab = (char**)ft_memalloc(sizeof(char*) * 4);
	tab[0] = ft_strdup("setenv");
	if (name)
		tab[1] = ft_strdup(name);
	if (value)
		tab[2] = ft_strdup(value);
	tab[3] = NULL;
	return (tab);
}

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

int			error_cd(char *str, int err)
{
	if (err == 1)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (err == 2)
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(str, 2);
	}
	return (1);
}

char		*change_path(char **tab, int i)
{
	ft_putendl(tab[i]);
	return (tab[i]);
}

int			check_arg_cd(char **tab, int i)
{
	int		len;

	len = len_array(tab);
	if (len - i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	else if (len - i == 2)
	{
		error_cd(tab[i], 1);
		return (-1);
	}
	return (i);
}

int			check_opt_cd(char **tab, int *opt)
{
	int		i;
	int		j;

	i = 1;
	*opt = 0;
	while (tab[i] && tab[i][0] == '-' && ft_strcmp(tab[i], "-"))
	{
		j = 1;
		while (tab[i][j])
		{
			if (tab[i][j] == 'P')
				*opt = 1;
			else if (tab[i][j] == 'L')
				*opt = 0;
			else if (tab[i][j] != '\0')
				return (check_arg_cd(tab, i));
			j++;
		}
		i++;
	}
	return (check_arg_cd(tab, i));
}

char		*load_path(char **tab, int i)
{
	char			buf[PATH_MAX];
	int				pos;
	char			**save;

	if ((pos = in_env("PWD", *env)) == -1)
		pos = pwdnotset(env);
	
}

int			cd_basic(char **tab, char ***env, int i, int opt)
{
	struct stat		st;
	int				islink;
	char			*path;

	path = NULL;
	if (lstat(tab[i], &st) == -1)
		return (print_error(1, tab[i]));
	if (S_ISDIR(st.st_mode) || (islink = S_ISLNK(st.st_mode)))
	{
		if (access(tab[i], R_OK) == -1)
			return (print_error(4, tab[i]));
		if (chdir(tab[i]) == -1)
			return (error_cd(tab[i], 2));
		ft_putnbrel(islink);
		path = load_path(tab, i, opt, islink);
		else if (islink == 1 && opt)
		{
			tab[i] = ft_strdup("/Users/hublanc/Documents/42sh/bugfix/test/");
			tab[i] = ft_strapp(tab[i], "kek");
			ft_putendl(tab[i]);
			if (readlink(tab[i], buf, sizeof(buf)) < 0)
				ft_putendl("ERROR");
			ft_putendl(buf);
		}
		change_pwd(env);
		return (0);
	}
	else
		return (error_cd(tab[i], 2));
}

int			ft_cd(char **tab, char ***env)
{
	int			len;
	int			i;
	int			opt;

	i = check_opt_cd(tab, &opt);
	if (i == -1)
		return (1);
	len = len_array(tab);
	if (len - i == 0 || (tab[i] && ft_strcmp(tab[i], "~") == 0))
		return (cd_home(env));
	else if (tab[i] && ft_strcmp(tab[i], "-") == 0)
		return (cd_prev(env));
	else
	{
		return (cd_basic(tab, env, i, opt));
		/*
		**	
		if ((perm = check_access(tab[i])) < 0)
			return (print_error(perm == -1 ? 1 : 4, tab[i]));
		chdir(tab[i]);
		change_pwd(env);
		return (0);*/
	}
	/*
	**	
	else
	{
		ft_putstr_fd("string not in pwd: ", 2);
		ft_putstr_fd(tab[1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}*/
}
