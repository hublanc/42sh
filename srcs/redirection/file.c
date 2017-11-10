/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 19:10:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/10 13:19:51 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*get_file(t_node *tree)
{
	int		i;
	char	*file;

	substitution(&tree->token, 0);
	file = NULL;
	i = len_io(tree->token);
	if ((tree->token)[i] == '>' && (tree->token)[i + 1] == '>')
		file = ft_strsub(tree->token, i + 3, ft_strlen(tree->token) - (i + 3));
	else if ((tree->token)[i] == '>')
		file = ft_strsub(tree->token, i + 2, ft_strlen(tree->token) - (i + 2));
	else if ((tree->token)[i] == '<' && (tree->token)[i + 1] != '<')
		file = ft_strsub(tree->token, i + 2, ft_strlen(tree->token) - (i + 2));
	return (file);
}

static void		abort_redir(t_node *tree)
{
	t_node	*tmp;
	int		*signal;

	tmp = tree;
	signal = singleton_status();
	*signal = 1;
	if (tmp->left)
		tmp->left->do_it = 1;
	while (tmp->left && tmp->value != 1)
		tmp = tmp->left;
	close_fd(tmp);
}

static int		authorization_file(char *path, t_node *tree, char *link)
{
	struct stat	s;

	ft_putcolor("FILE : ");
	ft_putendl(link);
	if (link[ft_strlen(link) - 1] == '/')
	{
		if (lstat(link, &s) != -1 && S_ISDIR(s.st_mode) && type_redir(tree->token) == 1)
			return (error_redir(path, "Is a directory"));
		else if (access(link, F_OK) == -1)
			return (error_redir(path, "Not a directory"));
	}
	if (access(link, F_OK) == -1 && type_redir(tree->token) == 1)
		return (0);
	else if (access(link, F_OK) == -1)
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

int				check_dir(char *path, char *dir)
{
	ft_putcolor("DIR : ");
	ft_putendl(dir);
	if (dir && dir[0] && access(dir, F_OK) == -1)
		return (error_redir(path, "No such file or directory"));
	else if (dir && dir[0] && access(dir, X_OK) == -1)
		return (error_redir(path, "Permission denied"));
	return (0);
}

static char		*check_file(char *file, t_node *tree)
{
	char	*dir;
	char	link[256];
	int		i;
	int		error;
	char	**split;

	if (readlink(file, link, 256) == -1)
		ft_strcpy(link, file);
	split = ft_strsplit(link, '/');
	i = 0;
	if (link[0] == '/')
		dir = ft_strdup("/");
	else
		dir = ft_strnew(0);
	error = check_dir(file, dir);
	while (split && split[i] && split[i + 1] && !error)
	{
		dir = ft_strapp(dir, split[i]);
		if (link[ft_strlen(dir)] == '/')
			dir = ft_strapp(dir, "/");
		error = check_dir(file, dir);
		i++;
	}
	if (error || authorization_file(file, tree, link))
	{
		abort_redir(tree);
		ft_strdel(&file);
	}
	ft_strdel(&dir);
	return (file);
}

int				open_file(t_node *tree)
{
	char	*file;
	int		fd;
	int		i;

	i = len_io(tree->token);
	file = get_file(tree);
	file = check_file(file, tree);
	fd = -1;
	if (!tree || !(tree->token) || !file)
		return (-1);
	if ((tree->token)[i] == '>' && (tree->token)[i + 1] == '>')
		fd = open(file,
				O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if ((tree->token)[i] == '>')
		fd = open(file,
				O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if ((tree->token)[i] == '<' && (tree->token)[i + 1] != '<')
		fd = open(file, O_RDONLY);
	ft_strdel(&file);
	return (fd);
}
