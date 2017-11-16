/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:39:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 13:08:12 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		authorization_dir(char *path, t_node *tree, char *link)
{
	char		*new;
	struct stat	s;

	if (lstat(link, &s) != -1 && S_ISDIR(s.st_mode)
			&& type_redir(tree->token) == 1)
		return (error_redir(path, "Is a directory"));
	new = ft_strdup(link);
	ft_strtrimlast(&new, '/');
	if (access(link, F_OK) == -1 && access(new, F_OK) != -1)
	{
		ft_strdel(&new);
		return (error_redir(path, "Not a directory"));
	}
	ft_strdel(&new);
	if (access(link, F_OK) == -1)
		return (error_redir(path, "No such file or directory"));
	return (0);
}

static int		authorization_file(char *path, t_node *tree, char *link)
{
	struct stat	s;

	if (link[ft_strlen(link) - 1] == '/'
			&& authorization_dir(path, tree, link))
		return (1);
	if (access(link, F_OK) == -1 && type_redir(tree->token) == 1)
		return (0);
	if (access(link, F_OK) == -1)
		return (error_redir(path, "No such file or directory"));
	else if (lstat(link, &s) != -1 && S_ISDIR(s.st_mode)
			&& type_redir(tree->token) == 1)
		return (error_redir(path, "Is a directory"));
	else if (access(link, F_OK) != -1
			&& ((access(link, W_OK) == -1 && type_redir(tree->token) == 1)
				|| (access(link, R_OK) == -1 && type_redir(tree->token) == 2)))
		return (error_redir(path, "Permission denied"));
	else if (access(link, F_OK) != -1
			&& ((!access(link, W_OK) && type_redir(tree->token) == 1)
				|| (!access(link, R_OK) && type_redir(tree->token) == 2)))
		return (0);
	return (1);
}

static int		check_dir(char *path, char *dir)
{
	if (dir && dir[0] && access(dir, F_OK) == -1)
		return (error_redir(path, "No such file or directory"));
	else if (dir && dir[0] && access(dir, X_OK | W_OK) == -1)
		return (error_redir(path, "Permission denied"));
	return (0);
}

static int		prep_check_dir(char **dir, char *link, char *file)
{
	int		i;
	char	**split;
	int		error;

	error = 0;
	i = 0;
	split = ft_strsplit(link, '/');
	*dir = (link[0] == '/') ? ft_strdup("/") : ft_strnew(0);
	if (link[0] == '/' && !ft_strcmp(link, ft_strrchr(link, '/'))
			&& ft_strcmp(link, "/"))
		error = check_dir(link, *dir);
	while (split && split[i] && split[i + 1] && !error)
	{
		*dir = ft_strapp(*dir, split[i]);
		if (link[ft_strlen(*dir)] == '/')
			*dir = ft_strapp(*dir, "/");
		error = check_dir(file, *dir);
		i++;
	}
	del_tabstr(&split);
	return (error);
}

char			*check_file(char *file, t_node *tree)
{
	char	*dir;
	char	link[256];
	int		error;

	if (file && ft_strlen(file) > 255)
	{
		abort_redir(tree);
		error_redir(file, "File name too long");
		ft_strdel(&file);
		return (file);
	}
	if (readlink(file, link, 255) == -1)
		ft_strcpy(link, file);
	error = 0;
	error = prep_check_dir(&dir, link, file);
	if (error || authorization_file(file, tree, link))
	{
		abort_redir(tree);
		ft_strdel(&file);
	}
	ft_strdel(&dir);
	return (file);
}
