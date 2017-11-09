/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:04:51 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/09 13:13:41 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			len_io(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && ft_isdigit(str[len]))
		len++;
	return (len);
}

int			type_redir(char *str)
{
	int	i;
	int	type;

	type = -1;
	i = len_io(str);
	if (!str)
		return (-1);
	if (str[i] && str[i] == '>' && str[i + 1] && (str[i + 1] == ' '
				|| str[i + 1] == '>'))
		type = 1;
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == ' ')
		type = 2;
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		type = 3;
	if (str[i] && str[i] == '<' && str[i + 1] && str[i + 1] == '&')
		type = 4;
	if (str[i] && str[i] == '>' && str[i + 1] && str[i + 1] == '&')
		type = 5;
	return (type);
}

int			exec_dup(int fd1, int fd2)
{
	if (fd2 < 0 || fd2 > 9)
	{
		ft_putstr_fd("file descriptor out of range: Bad file descriptor\n", 2);
		return (0);
	}
	if (dup2(fd1, fd2) == -1)
	{
		ft_putnbr_fd(fd1, 2);
		ft_putstr_fd(": Bad File descriptor\n", 2);
		return (0);
	}
	return (1);
}

int			do_redir(t_node *tree)
{
	int		i;

	i = 0;
	if (tree->redir_r && tree->fd_out)
	{
		while ((tree->fd_out)[i] != -1)
			i++;
		if (!exec_dup((tree->fd_out)[i - 1], (tree->fd_out_io)[i - 1]))
			return (-1);
	}
	else if (!exec_dup(tree->out, 1))
		return (-1);
	i = 0;
	if (tree->redir_l && tree->fd_in)
	{
		while ((tree->fd_in)[i] != -1)
			i++;
		if (!exec_dup((tree->fd_in)[i - 1], (tree->fd_in_io)[i - 1]))
			return (-1);
	}
	else if (!exec_dup(tree->in, 0))
		return (-1);
	return (1);
}

int			error_redir(char *file, char *reason)
{
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(reason, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(file, 2);
	return (1);
}
