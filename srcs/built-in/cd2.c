/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:16:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/10 12:57:49 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_dotdot(char **tmp)
{
	size_t	i;

	if (!*tmp)
		return ;
	while ((i = ft_strschr_len(*tmp, "..")))
	{
		while ((*tmp) && (*tmp)[i] != '/')
			ssupprchr(tmp, i);
		ssupprchr(tmp, i--);
		ssupprchr(tmp, i--);
		while ((*tmp) && (*tmp)[i] != '/')
			ssupprchr(tmp, i--);
	}
	(*tmp)[ft_strlen(*tmp) - 1] == '/' ? (*tmp)[ft_strlen(*tmp) - 1] = 0 : 0;
	if (!(*tmp)[0])
		(*tmp)[0] = '/';
}

int		change_envpwd(char *tmp, char ***env)
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

char	*check_path(char *path, char ***env, char opt)
{
	struct stat	atr;
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
		(tmp2) ? free(tmp2): 0;
	}
	else if (!(tmp = ft_strdup(path)))
		tmp = NULL;
	check_dotdot(&tmp);
	if (chdir(tmp) == -1)
	{
		if (lstat(tmp, &atr) == -1)
			ft_putstr_fd("cd: no such file or directory: ", 2);
		else
			ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	if (opt == 'P')
	{
		(tmp) ? free(tmp) : 0;
		tmp = (char *)ft_memalloc(1024);
		getcwd(tmp, 1024);
	}
	return (tmp);
}
