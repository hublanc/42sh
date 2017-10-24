/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:13:22 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/24 20:00:07 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node		*mark_fd(t_node *tree)
{
	t_node		*tmp;
	int			type;

	tmp = tree;
	if (!tree)
		return (tree);
	type = type_redir(tree->token);
	while (tmp->left && tmp->value != 1)
		tmp = tmp->left;
	if (type == 2)
		tmp->redir_l = 1;
	else if (type == 3)
		tmp->heredoc = 1;
	else if (type == 4 || type == 5)
		tmp->aggre = 1;
	else
		tmp->redir_r = 1;
	return (tmp);
}

void		close_fd(t_node *tree)
{
	int		i;

	i = 0;
	if (tree->fd_out)
	{
		while ((tree->fd_out)[i] != -1)
			close((tree->fd_out)[i++]);
		ft_memdel((void**)&(tree->fd_out));
	}
	i = 0;
	if (tree->fd_in)
	{
		while ((tree->fd_in)[i] != -1)
			close((tree->fd_in)[i++]);
		ft_memdel((void**)&(tree->fd_in));
	}
}

int			prep_fd(t_node *tree)
{
	if (do_redir(tree) == -1)
		return (-1);
	if (tree->heredoc)
		heredoc_input(tree);
	if (tree->aggre && exec_aggre(tree) == -1)
		return (-1);
	return (1);
}

int			manage_fd(t_node *tree)
{
	t_node		*tmp;
	int			i;

	if (substitution(&tree->token, 1) == -1)
		return (-1);
	i = len_io(tree->token);
	tmp = mark_fd(tree);
	if (type_redir(tree->token) == 4 || type_redir(tree->token) == 5)
		manage_aggre(tmp, tree);
	else if (type_redir(tree->token) == 1)
	{
		if (!(tmp->fd_out = add_fd(tmp->fd_out, tree)))
			return (-1);
		tmp->fd_out_io = add_io(tmp->fd_out_io, tree, 1);
	}
	else if (type_redir(tree->token) == 2)
	{
		if (!(tmp->fd_in = add_fd(tmp->fd_in, tree)))
			return (-1);
		tmp->fd_in_io = add_io(tmp->fd_in_io, tree, 0);
	}
	else if (type_redir(tree->token) == 3)
		manage_heredoc(tree, tmp);
	return (1);
}
