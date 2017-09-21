/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:00:36 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 17:53:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_onscreen(t_compl *compl, t_cmd *cmd, struct winsize w, int hided)
{
	t_coargs	*args;
	int			nbrpercol;
	int			nbrperline;
	int			i;

	args = &compl->args;
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	nbrperline = nbr_perline(compl->maxlen, w.ws_col);
	nbrpercol = nbr_percol(compl->nbrargs, nbrperline, w.ws_row, i);
	i = -1;
	while (++i < nbrpercol)
	{
		if (compl->curr >= compl->toskip + i * (hided + nbrpercol)
		&& compl->curr < compl->toskip + i * (hided + nbrpercol) + nbrpercol - i)
			return (1);
	}
	return (0);
}

static void	get_onscreen(t_compl *compl, t_cmd *cmd)
{
	struct winsize	w;
	int				nbrpercol;
	int				nbrperline;
	int				i;
	int				j;

	ioctl(0, TIOCGWINSZ, &w);
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	nbrperline = nbr_perline(compl->maxlen, w.ws_col);
	nbrpercol = nbr_percol(compl->nbrargs, nbrperline, w.ws_row, i);
	if (nbrpercol * nbrperline >= compl->nbrargs)
		return ;
	i = 1;
	while (i * nbrperline < compl->nbrargs - nbrpercol * nbrperline)
		i++;
	j = compl->toskip;
	while (compl->toskip <= i && !is_onscreen(compl, cmd, w, i))
		compl->toskip++;
	if (j > i)
	{
		compl->toskip = j - 1;
		while (compl->toskip > 0 && !is_onscreen(compl, cmd, w, i))
			compl->toskip--;
	}
}

static void	add_argtoline(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*args;

	args = &compl->args;
	while (args && compl->curr != args->id)
		args = args->next;
	if (args && args->arg)
		add_line(cmd, args->arg + ft_strlen(compl->arg));
}

int		compl_keys(t_compl *compl, t_cmd *cmd, char **buf)
{
	ft_bzero(*buf, ft_strlen(*buf));
	read(0, *buf, 999);
	if ((*buf)[0] == 27 && !(*buf)[1])
		return (-1);
	else if ((*buf)[0] == 27 && compl_arrow(compl, cmd, *buf))
		display_args(compl, cmd);
	else if ((*buf)[0] == 9 && !(*buf)[1])
	{
		compl->curr = (compl->curr < compl->nbrargs - 1) ? compl->curr + 1 : 0;
		get_onscreen(compl, cmd);
		display_args(compl, cmd);
	}
	else if ((*buf)[0] == 10 && !(*buf)[1])
	{
		add_argtoline(compl, cmd);
		return (-1);
	}
	else
		return (0);
	return (1);
}
