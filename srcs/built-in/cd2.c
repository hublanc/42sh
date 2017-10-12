/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:16:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 12:27:28 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_dotdot(char **tmp)
{
	size_t	i;

	if (!*tmp)
		return ;
	while ((i = ft_strschr_len(*tmp, "..")))
	{
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

static int	change_envpwd(char *tmp, char ***env)
{
	char	*tab[4];

	tab[0] = "setenv";
	tab[1] = "OLDPWD";
	tab[2] = tmp;
	tab[3] = 0;
	ft_setenv(tab, env);
	tab[0] = "setenv";
	tab[1] = "PWD";
	tab[2] = tmp;
	tab[3] = 0;
	ft_setenv(tab, env);
	return (1);
}

static int	change_cwd(char *tmp, char *path)
{
	struct stat	atr;

	if (chdir(tmp) == -1)
	{
		if (lstat(tmp, &atr) == -1)
			ft_putstr_fd("cd: no such file or directory: ", 2);
		else
			ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
}

static char	*check_path(char *path, char ***env, char opt)
{
	char		*tmp;
	char		*tmp2;

	if (path[0] != '/' && opt != 'P' && get_elem(env, "PWD="))
	{
		tmp2 = NULL;
		if (ft_strcmp(get_elem(env, "PWD="), "/"))
			tmp2 = ft_strjoin(get_elem(env, "PWD="), "/");
		else
			tmp2 = ft_strdup("/");
		tmp = ft_strjoin(tmp2, path);
		(tmp2) ? free(tmp2) : 0;
	}
	else if (!(tmp = ft_strdup(path)))
		tmp = NULL;
	check_dotdot(&tmp);
	if (!change_cwd(tmp, path))
		return (NULL);
	if (opt == 'P')
	{
		(tmp) ? free(tmp) : 0;
		tmp = (char *)ft_memalloc(1024);
		getcwd(tmp, 1024);
	}
	return (tmp);
}

void		change_pwd(char *path, char ***env, char opt)
{
	char	*tmp;

	if (!ft_strncmp(path, "~/", 2))
	{
		if (!(tmp = ft_strjoin(get_elem(env, "HOME="), (path + 1))))
			return ;
		path = tmp;
		free(tmp);
	}
	if (!(tmp = check_path(path, env, opt)))
		return ;
	change_envpwd(tmp, env);
	free(tmp);
}
