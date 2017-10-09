/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:16:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/09 14:40:17 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_elem(char ***env, char *elem)
{
	int	i;

	if (!env || !*env || !**env)
		return (NULL);
	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], elem, ft_strlen(elem)))
		i++;
	if (!(*env)[i])
		return (NULL);
	return ((*env)[i] + ft_strlen(elem));
}

int		change_envpwd(char *tmp, char ***env)
{
	char	*tab[4];

	tab[0] = "setenv";
	tab[1] = "OLDPWD";
	tab[2] = get_elem(env, "PWD=");
	tab[3] = 0;
	ft_setenv(tab, env);
	tab[0] = "setenv";
	tab[1] = "PWD";
	tab[2] = tmp;
	tab[3] = 0;
	ft_setenv(tab, env);
	free(tmp);
	return (1);
}

char	*check_path(char *path, char ***env)
{
	struct stat	atr;
	char		*tmp;

	if (chdir(path) == -1)
	{
		if (lstat(path, &atr) == -1)
			ft_putstr_fd("cd: no such file or directory: ", 2);
		else
			ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	if (path[0] == '/')
		return ((tmp = ft_strdup(path)));
	if (!(tmp = (char *)ft_memalloc(5001)))
	{
		chdir(get_elem(env, "PWD="));
		return (NULL);
	}
	getcwd(tmp, 5000);
	return (tmp);
}

void	check_dotdot(char **tmp, char **path)
{
	size_t	i;

	if (!*tmp)
		return ;
	i = ft_strlen(*tmp) - 1;
	while (ft_strschr(*path, ".."))
	{
		ssupprchr(tmp, i--);
		while ((*path)[0] && (*path)[0] != '/')
			ssupprchr(path, 0);
		while ((*path)[0] && (*path)[0] == '/')
			ssupprchr(path, 0);
		while ((*tmp) && (*tmp)[i] != '/')
			ssupprchr(tmp, i--);
		if (!(*path)[0])
			while ((*tmp) && (*tmp)[i] == '/')
				ssupprchr(tmp, i--);
	}
}
