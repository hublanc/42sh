/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:35:41 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/26 16:59:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		stock_buffer(t_cmd *cmd, int start)
{
	int		len;

	if (cmd->buffer)
		ft_strdel(&(cmd->buffer));
	if (start < cmd->col)
	{
		len = cmd->col - start;
		start = start - 1 - cmd->prlen;
		cmd->buffer = ft_strsub(cmd->str, start, len);
	}
	else if (start > cmd->col)
	{
		len = start - cmd->col;
		start = cmd->col - 1 - cmd->prlen;
		cmd->buffer = ft_strsub(cmd->str, start, len);
	}
}

void		cut_str(t_cmd *cmd, int start)
{
	int		i;

	if (start < cmd->col)
	{
		i = cmd->col - start - 1;
		while (i >= 0)
			cmd->str = ft_strdelone(cmd->str, (start + i--) - cmd->prlen);
	}
	else if (start > cmd->col)
	{
		i = start - cmd->col - 1;
		while (i >= 0)
			cmd->str = ft_strdelone(cmd->str, (cmd->col + i--) - cmd->prlen);
	}
}

void		left_handler(t_cmd *cmd, int *swap, int start)
{
	if ((cmd->str)[(cmd->col - 1) - cmd->prlen] != '\0'
			&& (*swap == 0 || *swap == 1))
	{
		*swap = 1;
		print_charev(cmd);
	}
	else if (*swap == 2 && (cmd->str)[(cmd->col - 1) - cmd->prlen] != '\0')
		isatty(0) ? ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]) : 0;
	if ((cmd->str)[(cmd->col - 1) - cmd->prlen] != '\0'
			&& cmd->col % cmd->sc_col != 0)
		isatty(0) ? tputs(tgetstr("le", NULL), 1, tputchar) : 0;
	go_left(cmd);
	if (*swap == 2 && cmd->col == start)
		*swap = 0;
}

void		right_handler(t_cmd *cmd, int *swap, int start)
{
	if (*swap == 2 || *swap == 0)
	{
		*swap = 2;
		print_charev(cmd);
	}
	else
		isatty(0) ? ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]) : 0;
	if (cmd->col % cmd->sc_col == 0)
	{
		isatty(0) ? tputs(tgetstr("cr", NULL), 1, tputchar) : 0;
		isatty(0) ? tputs(tgetstr("do", NULL), 1, tputchar) : 0;
	}
	cmd->col++;
	if (*swap == 1 && cmd->col == start)
		*swap = 0;
}
