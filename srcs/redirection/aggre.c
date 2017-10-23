/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:07:57 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/23 19:28:36 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		manage_aggre(t_node *cmd, t_node *redir)
{
	int		cut;

	cut = len_io(redir->token) + 3;
	if (type_redir(redir->token) == 4)
	{
		cmd->aggre_in_nb = add_io(cmd->aggre_in_nb, redir, 0);
		cmd->aggre_in_w = add_w(cmd->aggre_in_w, redir, cut);
	}
	else if (type_redir(redir->token) == 5)
	{
		cmd->aggre_out_nb = add_io(cmd->aggre_out_nb, redir, 1);
		cmd->aggre_out_w = add_w(cmd->aggre_out_w, redir, cut);
	}
}

int			*add_fd_aggre(int *fds, int fd)
{
	int		*new;
	int		i;

	i = 0;
	if (!fds)
	{
		new = (int*)ft_memalloc(sizeof(int) * 2);
		new[0] = fd;
		new[1] = -1;
		return (new);
	}
	while (fds[i] != -1)
		i++;
	new = (int*)ft_memalloc(sizeof(int) * (i + 2));
	i = 0;
	while (fds[i] != -1)
	{
		new[i] = fds[i];
		i++;
	}
	new[i++] = fd;
	new[i] = -1;
	ft_memdel((void**)&fds);
	return (new);
}

int			dup_file(t_node *tree, int i)
{
	int		fd;

	fd = open(tree->aggre_out_w[i]
			, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	tree->fd_out = add_fd_aggre(tree->fd_out, fd);
	if (!exec_dup(fd, tree->aggre_out_nb[i]))
		return (-1);
	return (1);
}

int			sub_aggre(t_node *tree)
{
	int		i;

	i = 0;
	while (tree->aggre_out_w && tree->aggre_out_w[i] != NULL)
	{
		if (!ft_strcmp(tree->aggre_out_w[i], "-"))
			close(tree->aggre_out_nb[i]);
		else if (ft_strfullnb(tree->aggre_out_w[i]))
		{
			if (!exec_dup(ft_atoi(tree->aggre_out_w[i]),
						tree->aggre_out_nb[i]))
				return (-1);
		}
		else
		{
			if (dup_file(tree, i) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}

int			exec_aggre(t_node *tree)
{
	int		i;

	i = 0;
	while (tree->aggre_in_w && tree->aggre_in_w[i] != NULL)
	{
		if (!ft_strcmp(tree->aggre_in_w[i], "-"))
			close(tree->aggre_in_nb[i]);
		else if (ft_strfullnb(tree->aggre_in_w[i]))
		{
			if (!exec_dup(ft_atoi(tree->aggre_in_w[i]),
						tree->aggre_in_nb[i]))
				return (-1);
		}
		else
		{
			ft_putstr_fd("ambigous redirection\n", 2);
			return (-1);
		}
		i++;
	}
	return (sub_aggre(tree));
}
