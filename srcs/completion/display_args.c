/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:35:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 15:56:25 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	nbr_perline(int maxlen, int w)
{
	int	i;

	i = 1;
	while (i * maxlen < w)
		i++;
	return ((--i > 0) ? i : 1);
}

static int	nbr_percol(int nbrargs, int nbrperline, int h, int rowline)
{
	int	i;

	i = 1;
	while (i * nbrperline < nbrargs)
		i++;
	if (i > h - rowline)
		return (h - rowline);
	return (i);
}

static int	maxrow_line(int lenline, int w)
{
	int	i;

	i = 1;
	while (i * w <  lenline)
		i++;
	return (i);
}

static int	print_col(t_compl *compl, t_coargs **args, int nbrpercol, int nbrright)
{
	int			count;
	int			i;

	count = 0;
	while (*args && (*args)->arg)
	{
		tputs(tgetstr("me", NULL), 1, tputchar);
		if (compl->curr == (*args)->id)
			tputs(tgetstr("mr", NULL), 1, tputchar);
		ft_putstr((*args)->arg);
		i = compl->maxlen - ft_strlen((*args)->arg);
		while (--i)
			ft_putchar(' ');
		tputs(tgetstr("me", NULL), 1, tputchar);
		ft_putchar(' ');
		(*args) = (*args)->next;
		if (--nbrpercol == 0)
			return (count);
		tputs(tgetstr("do", NULL), 1, tputchar);
		i = nbrright;
		while (i--)
			tputs(tgetstr("nd", NULL), 1, tputchar);
		count++;
	}
	return (count);
}

void		print_args(t_compl *compl, t_cmd *cmd, struct winsize w)
{
	t_coargs	*args;
	int			nbrperline;
	int			nbrpercol;
	int			i;
	int			j;

	args = &compl->args;
	nbrperline = nbr_perline(compl->maxlen, w.ws_col);
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	nbrpercol = nbr_percol(compl->nbrargs, nbrperline, w.ws_row, i);
	j = -1;
	while (++j < nbrperline && args)
	{
		i = print_col(compl, &args, nbrpercol, compl->maxlen * j);
		while (i--)
			tputs(tgetstr("up", NULL), 1, tputchar);
		i = 0;
		while (args && ++i * nbrperline < compl->nbrargs - nbrpercol * nbrperline)
			args = args->next;
	}
	i = j * compl->maxlen;
	while (i--)
		tputs(tgetstr("le", NULL), 1, tputchar);
}

void		display_args(t_compl *compl, t_cmd *cmd)
{
	struct winsize	w;
	int				i;

	go_begin(cmd->col, cmd->sc_col);
	ioctl(0, TIOCGWINSZ, &w);
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	while (i--)
		tputs(tgetstr("do", NULL), 1, tputchar);
	print_args(compl, cmd, w);
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	while (i--)
		tputs(tgetstr("up", NULL), 1, tputchar);
	choose_prompt(cmd);
	ft_putstr(cmd->str);
}
