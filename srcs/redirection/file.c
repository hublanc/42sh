/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 19:10:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 18:20:55 by lbopp            ###   ########.fr       */
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

static int		authorization_file(char *path, t_node *tree)
{
	struct stat		buf;

	if (type_redir(tree->token) == 1 && path && access(path, F_OK) == -1)
		if (!ft_strrchr(path, '/') || lstat(ft_strrchr(path, '/'), &buf) != -1)
			return (0);
	if (lstat(path, &buf) == -1)
	{
		ft_putstr_fd("shell: permission denied: ", 2);
		ft_putendl_fd(path, 2);
		return (-2);
	}
	if (type_redir(tree->token) == 1)
	{
		if (S_ISDIR(buf.st_mode))
		{
			ft_putstr_fd("shell: is a directory: ", 2);
			ft_putendl_fd(path, 2);
			return (-1);
		}
	}
	return (0);
}

static char		*check_file(char *file, t_node *tree)
{
	int		error;
	int		i;

	i = len_io(tree->token);
	error = 0;
	if (ft_strcmp(file, "/"))
		ft_strtrimlast(&file, '/');
	if (file && access(file, F_OK) != -1)
	{
		if (((tree->token)[i] == '>') && access(file, W_OK) == -1)
			error = print_error(4, file);
		else if ((tree->token)[i] == '<' && (tree->token)[i + 1] != '<'
				&& access(file, R_OK) == -1)
			error = print_error(4, file);
	}
	else
		if ((tree->token)[i] == '<' && (tree->token)[i + 1] != '<'
				&& access(file, R_OK) == -1)
			error = print_error(1, file);
	if (error || authorization_file(file, tree) < 0)
	{
		abort_redir(tree);
		ft_strdel(&file);
	}
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
