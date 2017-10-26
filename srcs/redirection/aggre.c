/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 14:07:57 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/26 11:20:02 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		manage_aggre(t_node *cmd, t_node *redir)
{
	int		cut;

	cut = ft_isdigit((redir->token)[0]) ? 4 : 3;
	if (ft_strchr(redir->token, '<'))
	{
		cmd->aggre_in_nb = add_io(cmd->aggre_in_nb, redir, 0);
		cmd->aggre_in_w = add_w(cmd->aggre_in_w, redir, cut);
	}
	else if (ft_strchr(redir->token, '>'))
	{
		cmd->aggre_out_nb = add_io(cmd->aggre_out_nb, redir, 1);
		cmd->aggre_out_w = add_w(cmd->aggre_out_w, redir, cut);
	}
}

int			exec_dup(char *word, int fd2)
{
	int		fd1;

	fd1 = ft_atoi(word);
	if (dup2(fd1, fd2) == -1)
	{
		ft_putnbr_fd(fd1, 2);
		ft_putstr_fd(": Bad file descriptor\n", 2);
		return (-1);
	}
	return (0);
}

int			*add_fd_aggre(int *fds, int fd)
{
	int		*new;
	int		i;

	i = 0;
	if (!fds)
	{
		if (!(new = (int*)ft_memalloc(sizeof(int) * 1)))
			return (NULL);
		new[0] = fd;
		new[1] = -1;
		return (new);
	}
	while (fds[i] != -1)
		i++;
	if (!(new = (int*)ft_memalloc(sizeof(int) * (i + 1))))
		return (NULL);
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

void		dup_file(t_node *tree, int i)
{
	int		fd;

	fd = open(tree->aggre_out_w[i]
			, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dup2(fd, tree->aggre_out_nb[i]);
	tree->fd_out = add_fd_aggre(tree->fd_out, fd);
}

int			exec_aggre(t_node *tree)
{
	int		i;

	i = 0;
	while (tree->aggre_in_w && tree->aggre_in_w[i] != NULL)
	{
		if (!ft_strcmp(tree->aggre_in_w[i], "-"))
			close(tree->aggre_in_nb[i]);
		else if (ft_strfullnb(tree->aggre_in_w[i]) &&
				exec_dup(tree->aggre_in_w[i], tree->aggre_in_nb[i]) == -1)
			return (-1);
		else
			ft_putstr_fd("file number expected\n", 2);
		i++;
	}
	i = 0;
	while (tree->aggre_out_w && tree->aggre_out_w[i] != NULL)
	{
		if (!ft_strcmp(tree->aggre_out_w[i], "-"))
			close(tree->aggre_out_nb[i]);
		else if (ft_strfullnb(tree->aggre_out_w[i])
				&& exec_dup(tree->aggre_out_w[i], tree->aggre_out_nb[i]) == -1)
			return (-1);
		else
			dup_file(tree, i);
		i++;
	}
	return (0);
}
