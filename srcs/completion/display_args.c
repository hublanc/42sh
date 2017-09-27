/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:35:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/27 17:09:01 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			*get_size(t_compl *compl, t_cmd *cmd)
{
	struct winsize	w;
	int				*size;

	if (!(size = (int*)ft_memalloc(sizeof(int) * 7)))
		return (NULL);
	ioctl(0, TIOCGWINSZ, &w);
	size[0] = w.ws_col;
	size[2] = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	size[1] = w.ws_row - size[2];
	size[3] = nbr_perline(compl->maxlen, w.ws_col);
	size[4] = nbr_percol(compl->nbrargs, size[3]);
	size[5] = 0;
	size[6] = 0;
	return (size);
}

static void	buff_arg(t_compl *compl, t_coargs *ar, char **buff, int *size)
{
	int	i;

	buffcat(buff, tgetstr("do", NULL));
	i = compl->maxlen * size[6];
	while (i--)
		buffcat(buff, tgetstr("nd", NULL));
	if (ar->id == compl->curr)
		buffcat(buff, tgetstr("mr", NULL));
	buffcat(buff, ar->color);
	buffcat(buff, ar->arg);
	buffcat(buff, RESET);
	i = 0;
	while ((size_t)++i < compl->maxlen - ft_strlen(ar->arg))
		buffcat(buff, " ");
	buffcat(buff, tgetstr("me", NULL));
	buffcat(buff, " ");
}

static void	print_args(t_compl *compl, int *size, char **buff)
{
	t_coargs	*ar;
	int			i;

	ar = &compl->args;
	i = compl->toskip;
	while (ar && i-- > 0)
		ar = ar->next;
	while (ar)
	{
		buff_arg(compl, ar, buff, size);
		ar = ar->next;
		if (++size[5] == size[4] || size[5] == size[1])
		{
			size[6]++;
			while (size[5]-- > 0)
				buffcat(buff, tgetstr("up", NULL));
			i = compl->toskip + (size[4] - (compl->toskip + size[1]));
			while (ar && i-- > 0)
				ar = ar->next;
			size[5] = 0;
		}
	}
}

void		get_curr(t_compl *compl)
{
	t_coargs *ar;

	if (compl->curr < 0)
		return ;
	ar = &compl->args;
	while (ar)
	{
		if (compl->curr == ar->id)
		{
			compl->ar = ar;
			return ;
		}
		ar = ar->next;
	}
}

void		display_args(t_compl *compl, t_cmd *cmd)
{
	char			*buff;
	int				*size;

	if (!(size = get_size(compl, cmd)))
		return ;
	buff = (char *)ft_memalloc(COMPLBUFF);
	go_begin(cmd->col + ((compl->ar) ? ft_strlen(compl->ar->arg) : 0), size[0]);
	get_curr(compl);
	buffcat(&buff, tgetstr("cd", NULL));
	if ((size_t)size[0] < compl->maxlen)
		print_complline(compl, cmd, size, &buff);
	if ((size_t)size[0] < compl->maxlen)
		return ;
	size[6] = size[2];
	while (--size[6])
		buffcat(&buff, tgetstr("do", NULL));
	size[6] = 0;
	print_args(compl, size, &buff);
	size[5] += size[2];
	while (--size[5])
		buffcat(&buff, tgetstr("up", NULL));
	buffcat(&buff, tgetstr("cr", NULL));
	print_complline(compl, cmd, size, &buff);
	print_buff(&buff);
	free(buff);
}
