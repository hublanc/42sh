/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:13:22 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/14 16:50:33 by hublanc          ###   ########.fr       */
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
	if ((tree->token)[0] == '<' && (tree->token)[1] != '<')
		type = 2;
	else if ((tree->token)[0] == '<' && (tree->token)[1] == '<')
		type = 3;
	else if (ft_strchr(tree->token, '&'))
		type = 4;
	else
		type = 1;
	while (tmp->left && tmp->value != 1)
		tmp = tmp->left;
	if (type == 2)
		tmp->redir_l = 1;
	else if (type == 3)
		tmp->heredoc = 1;
	else if (type == 4)
		tmp->aggre = 1;
	else
		tmp->redir_r = 1;
	return (tmp);
}

int			open_file(t_node *tree)
{
	char	*file;
	int		fd;
	int		i;

	i = ft_isdigit((tree->token)[0]) ? 1 : 0;
	file = NULL;
	fd = -1;
	if (!tree || !(tree->token))
		return (1);
	if ((tree->token)[i] == '>' && (tree->token)[i + 1] == '>')
	{
		file = ft_strsub(tree->token, i + 3, ft_strlen(tree->token) - (i + 3));
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP |S_IROTH);
	}
	else if ((tree->token)[i] == '>' || ((tree->token)[i] == '<' 
			&& (tree->token)[i + 1] != '<'))
	{
		file = ft_strsub(tree->token, i + 2, ft_strlen(tree->token) - (i + 2));
		fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP |S_IROTH);
	}
	ft_strdel(&file);
	return (fd);
}

void	close_fd(t_node *tree)
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

void	prep_fd(t_node *tree)
{
	int		i;

	i = 0;
	if (tree->redir_r && tree->fd_out)
	{
		while ((tree->fd_out)[i] != -1)
			i++;
		dup2((tree->fd_out)[i - 1], (tree->fd_out_io)[i - 1]);
	}
	else
		dup2(tree->out, 1);
	i = 0;
	if (tree->heredoc)
		heredoc_input(tree);
	if (tree->aggre)
		exec_aggre(tree);
	if (tree->redir_l && tree->fd_in)
	{
		while ((tree->fd_in)[i] != -1)
			i++;
		dup2((tree->fd_in)[i - 1], (tree->fd_in_io)[i - 1]);
	}
	else
		dup2(tree->in, 0);
}

void		manage_fd(t_node *tree)
{
	t_node		*tmp;
	int			i;

	i = ft_isdigit((tree->token)[0]) ? 1 : 0;
	tmp = mark_fd(tree);
	if (ft_strchr(tree->token, '&'))
		manage_aggre(tmp, tree);
	else if ((tree->token)[i] == '>')
	{
		tmp->fd_out = add_fd(tmp->fd_out, tree);
		tmp->fd_out_io = add_io(tmp->fd_out_io, tree, 1);
	}
	else if ((tree->token)[i] == '<' && (tree->token)[i + 1] != '<')
	{
		tmp->fd_in = add_fd(tmp->fd_in, tree);
		tmp->fd_in_io = add_io(tmp->fd_in_io, tree, 0);
	}
	else if ((tree->token)[i] == '<' && (tree->token)[i + 1] == '<')
		tmp->heredoc_str = ft_strsub(tree->token, i + 3, ft_strlen(tree->token) - (i + 3));
}
