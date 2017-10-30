/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_chdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:03:01 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/30 17:29:22 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	free_pwd is used to know if pwd was malloced (= 1) or not (= 0)
*/

int		error_chdir(char **pwd, char *arg, int free_pwd)
{
	struct stat	s;
	int			ret;

	if ((ret = lstat(*pwd, &s)) != -1
			&& S_ISDIR(s.st_mode) && !(s.st_mode & S_IXUSR))
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else if (ret != -1 && !S_ISDIR(s.st_mode))
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Not a directory", 2);
	}
	else
	{
		ft_putstr_fd("42sh: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (free_pwd)
		ft_strdel(pwd);
	return (1);
}
