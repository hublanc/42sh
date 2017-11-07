/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:47:27 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 17:00:02 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_begin(int pos, int col)
{
	if (!ttyyyy(0))
		return ;
	while (pos > col)
	{
		tputs(tgetstr("up", NULL), 1, tputchar);
		pos -= col;
	}
	tputs(tgetstr("cr", NULL), 1, tputchar);
}

void		go_right(t_cmd *cmd)
{
	if (!ttyyyy(0))
	{
		cmd->col++;
		return ;
	}
	if (cmd->col % cmd->sc_col == 0)
	{
		tputs(tgetstr("cr", NULL), 1, tputchar);
		tputs(tgetstr("do", NULL), 1, tputchar);
	}
	else
		tputs(tgetstr("nd", NULL), 1, tputchar);
	cmd->col++;
}

void		go_left(t_cmd *cmd)
{
	int		col;

	if (!ttyyyy(0))
	{
		cmd->col--;
		return ;
	}
	col = cmd->sc_col;
	if (cmd->col % cmd->sc_col == 1)
	{
		tputs(tgetstr("up", NULL), 1, tputchar);
		while (col-- > 0)
			tputs(tgetstr("nd", NULL), 1, tputchar);
	}
	else
		tputs(tgetstr("le", NULL), 1, tputchar);
	cmd->col--;
}

void		seek_lword(t_cmd *cmd)
{
	int		count;
	int		i;

	if (!cmd->str)
		return ;
	i = (cmd->col - 1) - cmd->prlen;
	count = 0;
	while (i >= 0 && cmd->str[i] > 32 && cmd->str[i] < 127)
	{
		i--;
		count++;
	}
	while (i >= 0 && cmd->str[i--] <= 32)
		count++;
	while (i >= 0 && cmd->str[i] > 32 && cmd->str[i--] < 127)
		count++;
	while (count-- > 0 && cmd->col > cmd->prlen + 1)
		go_left(cmd);
}

void		seek_rword(t_cmd *cmd)
{
	int		count;
	int		i;

	if (!cmd->str)
		return ;
	i = (cmd->col - 1) - cmd->prlen;
	count = 0;
	while (cmd->str[i] > 32 && cmd->str[i] < 127)
	{
		i++;
		count++;
	}
	while (cmd->str[i++] == 32)
		count++;
	while (count-- > 0)
		go_right(cmd);
}
