/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 19:10:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/10 14:44:11 by lbopp            ###   ########.fr       */
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

void			abort_redir(t_node *tree)
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
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if ((tree->token)[i] == '>')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if ((tree->token)[i] == '<' && (tree->token)[i + 1] != '<')
		fd = open(file, O_RDONLY);
	ft_strdel(&file);
	return (fd);
}
