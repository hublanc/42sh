/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:35:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 12:13:33 by amazurie         ###   ########.fr       */
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

	if (nbrargs / (nbrperline + 1) > h - rowline)
		return (h - rowline);
	i = 1;
	while (i * nbrperline < nbrargs)
		i++;
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

void		print_args(t_compl *compl, struct winsize w, int maxrowline)
{
	t_coargs	*args;
	int			nbrperline;
	int			maxprintable;
	int			i;

	nbrperline = nbr_perline(compl->maxlen, w.ws_col);
	maxprintable = nbrperline * nbr_percol(compl->nbrargs, nbrperline,
			w.ws_row, maxrowline);
	args = &compl->args;
	while (args)
	{
		if (nbrperline == 0)
		{
			ft_putchar('\n');
			nbrperline = nbr_perline(compl->maxlen, w.ws_col);
		}
		ft_putstr(args->arg);
		i = compl->maxlen - ft_strlen(args->arg);
		while (i--)
			ft_putchar(' ');
		args = args->next;
		nbrperline--;
		maxprintable--;
		if (maxprintable == 0)
			return ;
	}
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
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	print_args(compl, w, i);
	// temporaire, a venir : revenir a la position sur la ligne en cours
	// d'edition selon la position apres l'affichage des arguments
	i = i + nbr_percol(compl->nbrargs,
			nbr_perline(compl->maxlen, w.ws_col), w.ws_row, i) - 1;
	while (i--)
		tputs(tgetstr("up", NULL), 1, tputchar);
	while (w.ws_col--)
		tputs(tgetstr("le", NULL), 1, tputchar);
	choose_prompt(cmd);
	ft_putstr(cmd->str);
}
