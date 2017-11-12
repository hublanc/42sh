/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_chdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:03:01 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/12 14:25:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	print_cd_error(char *arg, char *reason)
{
	ft_putstr_fd("shell: cd: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(reason, 2);
	return (1);
}

static int	check_each_dir(char *pwd, char *arg)
{
	char		*new;

	new = ft_strdup(pwd);
	add_slash(&new);
	if (access(pwd, F_OK) == -1)
		print_cd_error(arg, ": No such file or directory");
	else if (access(new, F_OK) == -1 && access(pwd, F_OK) != -1)
		print_cd_error(arg, ": Not a directory");
	else if (access(new, F_OK | X_OK) == -1)
		print_cd_error(arg, ": Permission denied");
	else
	{
		ft_strdel(&new);
		return (0);
	}
	ft_strdel(&new);
	return (1);
}

static int	prep_check_dir(char **dir, char *split, char *link, char *arg)
{
	*dir = ft_strapp(*dir, split);
	if (link[ft_strlen(*dir)] == '/')
		*dir = ft_strapp(*dir, "/");
	return (check_each_dir(*dir, arg));
}

/*
**	free_pwd is used to know if pwd was malloced (= 1) or not (= 0)
*/

int			error_chdir(char **pwd, char *arg, int free_pwd)
{
	char	*dir;
	char	link[PATH_MAX + 1];
	int		i;
	int		error;
	char	**split;

	if (readlink(*pwd, link, PATH_MAX) == -1)
		ft_strcpy(link, *pwd);
	if (free_pwd)
		ft_strdel(pwd);
	if (ft_strlen(arg) > 255)
		return (print_cd_error(arg, ": File name too long"));
	split = ft_strsplit(link, '/');
	i = 0;
	error = 0;
	dir = (link[0] == '/') ? ft_strdup("/") : ft_strnew(0);
	if (link[0] == '/' && !ft_strcmp(link, ft_strrchr(link, '/'))
			&& ft_strcmp(link, "/"))
		error = check_each_dir(dir, arg);
	while (split && split[i] && split[i] && !error)
		error = prep_check_dir(&dir, split[i++], link, arg);
	ft_strdel(&dir);
	del_tabstr(&split);
	return (1);
}
