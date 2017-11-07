/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:28:26 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 12:44:53 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	control_arrow(char *str, t_cmd *cmd)
{
	int		save;

	if (str[3] == 65 && cmd->col > cmd->sc_col)
	{
		cmd->col -= cmd->sc_col;
		if (cmd->col < cmd->prlen + 1)
		{
			while (cmd->col != cmd->prlen + 1)
				go_right(cmd);
		}
		isatty(0) ? tputs(tgetstr("up", NULL), 1, tputchar) : 0;
	}
	if (str[3] == 66 && (int)ft_strlen(cmd->str) + cmd->prlen + 1 > cmd->sc_col)
	{
		save = cmd->sc_col;
		while (save-- > 0
		&& cmd->col < (int)ft_strlen(cmd->str) + cmd->prlen + 1)
			go_right(cmd);
	}
	if (str[3] == 68)
		seek_lword(cmd);
	if (str[3] == 67)
		seek_rword(cmd);
}

void		control_homend(char *str, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (str[2] == 72)
	{
		go_begin(cmd->col, cmd->sc_col);
		cmd->col = 1;
		while (i++ < cmd->prlen)
			go_right(cmd);
		cmd->col = cmd->prlen + 1;
	}
	else if (str[2] == 70)
	{
		i = (int)ft_strlen(cmd->str) + 1;
		while (cmd->col < cmd->prlen + i)
			go_right(cmd);
	}
}

void		arrow_handler(char *str, t_cmd *cmd, t_control **hist)
{
	if (str[2] == 68 && cmd && cmd->col > cmd->prlen + 1)
		go_left(cmd);
	else if (str[2] == 67 && cmd
			&& cmd->col < (int)ft_strlen(cmd->str) + cmd->prlen + 1)
		go_right(cmd);
	else if (isatty(0) && isatty(2) && str[2] == 65)
		seek_next(hist, cmd);
	else if (isatty(0) && isatty(2) && str[2] == 66)
		seek_prev(hist, cmd);
	else if ((cmd && (size_t)cmd->col - cmd->prlen - 1 < ft_strlen(cmd->str))
		&& ((str[1] == 91 && str[2] == 51 && str[3] == 126) || str[0] == 4))
	{
		cmd->str = ft_strdelone(cmd->str, cmd->col - cmd->prlen);
		print_line(cmd);
	}
	if (str[1] == 27 && str[2] == 91)
		control_arrow(str, cmd);
	if (str[1] == 91)
		control_homend(str, cmd);
}
