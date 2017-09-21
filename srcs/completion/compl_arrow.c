#include "shell.h"

static void	gest_left(t_compl *compl, t_cmd *cmd)
{
	struct winsize	w;
	int				nbrpercol;
	int				nbrperline;
	int				i;

	ioctl(0, TIOCGWINSZ, &w);
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	nbrperline = nbr_perline(compl->maxlen, w.ws_col);
	nbrpercol = nbr_percol(compl->nbrargs, nbrperline, w.ws_row, i);
	i = nbrpercol;
	if (nbrpercol * nbrperline < compl->nbrargs)
	{
		i = 1;
		while (i * nbrperline < compl->nbrargs - nbrpercol * nbrperline)
			i++;
	}
	if (nbrperline == 1)
		compl->curr = (compl->curr > 0) ? compl->curr - 1 : compl->nbrargs - 1;
	else if (compl->curr - i >= 0)
		compl->curr -= i;
	else
	{
		while (compl->curr + i < compl->nbrargs)
			compl->curr += i;
		if (compl->curr + i == compl->nbrargs)
			compl->curr = compl->nbrargs - 1;
		else if (compl->curr - 1 < compl->nbrargs - i)
			compl->curr = compl->nbrargs - i;
		else
			compl->curr -= 1;
	}
}

static void	gest_right(t_compl *compl, t_cmd *cmd)
{
	struct winsize	w;
	int				nbrpercol;
	int				nbrperline;
	int				i;

	ioctl(0, TIOCGWINSZ, &w);
	i = maxrow_line(ft_strlen(cmd->str) + ft_strlen(cmd->prompt)
			+ compl->maxlen, w.ws_col);
	nbrperline = nbr_perline(compl->maxlen, w.ws_col);
	nbrpercol = nbr_percol(compl->nbrargs, nbrperline, w.ws_row, i);
	i = nbrpercol;
	if (nbrpercol * nbrperline < compl->nbrargs)
	{
		i = 1;
		while (i * nbrperline < compl->nbrargs - nbrpercol * nbrperline)
			i++;
	}
	if (nbrperline == 1)
		compl->curr = (compl->curr < compl->nbrargs - 1) ? compl->curr + 1 : 0;
	else if (compl->curr + i < compl->nbrargs)
		compl->curr += i;
	else
	{
		while (compl->curr - i >= 0)
			compl->curr -= i;
		if (++compl->curr >= i)
			compl->curr = 0;
	}
}

int			compl_arrow(t_compl *compl, t_cmd *cmd, char *buf)
{
	if (buf[2] == 68)
		gest_left(compl, cmd);
	else if (buf[2] == 67)
		gest_right(compl, cmd);
	else if (buf[2] == 65)
		compl->curr = (compl->curr > 0) ? compl->curr - 1 : compl->nbrargs - 1;
	else if (buf[2] == 66)
		compl->curr = (compl->curr < compl->nbrargs - 1) ? compl->curr + 1 : 0;
	else
		return (0);
	if (compl || cmd || buf)
		;
	return (1);
}
