/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:46:37 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 20:35:36 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			print_charev(t_cmd *cmd)
{
	tputs(tgetstr("mr", NULL), 1, tputchar);
	ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]);
	tputs(tgetstr("me", NULL), 1, tputchar);
}

void			print_up(int nb, int n)
{
	tputs(tgetstr("sc", NULL), 1, tputchar);
	tputs(tgetstr("ho", NULL), 1, tputchar);
	ft_putnbr(nb);
	tputs(tgetstr("do", NULL), 1, tputchar);
	ft_putnbr(n);
	tputs(tgetstr("rc", NULL), 1, tputchar);
}

void			stock_buffer(t_cmd *cmd, int start)
{
	int			len;

	if(cmd->buffer)
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

void			cut_str(t_cmd *cmd, int start)
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

void			left_handler(t_cmd *cmd, int *swap, int start)
{
	if ((cmd->str)[(cmd->col - 1) - cmd->prlen] != '\0'
		&& (*swap == 0 || *swap == 1))
	{
		*swap = 1;
		print_charev(cmd);
	}
	else if (*swap == 2 && (cmd->str)[(cmd->col - 1) - cmd->prlen] != '\0')
		ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]);
	if ((cmd->str)[(cmd->col - 1) - cmd->prlen] != '\0'
	&& cmd->col % cmd->sc_col != 0)
		tputs(tgetstr("le", NULL), 1, tputchar);
	go_left(cmd);
	if (*swap == 2 && cmd->col == start)
		*swap = 0;
}

void			right_handler(t_cmd *cmd, int *swap, int start)
{
	if (*swap == 2 || *swap == 0)
	{
		*swap = 2;
		print_charev(cmd);
	}
	else
		ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]);
	if (cmd->col % cmd->sc_col == 0)
	{
		tputs(tgetstr("cr", NULL), 1, tputchar);
		tputs(tgetstr("do", NULL), 1, tputchar);
	}
	cmd->col++;
	if (*swap == 1 && cmd->col == start)
		*swap = 0;
}

void			core_handler(t_cmd *cmd, char *buf, int *swap, int start)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68
			&& cmd->col > cmd->prlen + 1)
		left_handler(cmd, swap, start);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67
			&& cmd->col < (int)ft_strlen(cmd->str) + cmd->prlen + 1)
		right_handler(cmd, swap, start);

}

void			cut_handler(t_cmd *cmd)
{
	char		buf[6];
	int			swap;
	int			start;

	swap = 0;
	start = cmd->col;
	bzero(buf, 6);
	while (buf[0] != -30 && buf[1] != -119 && buf[2] != -120)
	{
		bzero(buf, 6);
		read(0, buf, 5);
		core_handler(cmd, buf, &swap, start);
	}
	stock_buffer(cmd, start);
	cut_str(cmd, start);
	print_line(cmd);
	if (cmd->col > (int)ft_strlen(cmd->str) + cmd->prlen)
	{
		while (cmd->col > (int)ft_strlen(cmd->str) + cmd->prlen + 1)
			go_left(cmd);
	}
}

void			paste_handler(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = cmd->col - 1 - cmd->prlen;
	if (!cmd->buffer)
		return ;
	while ((cmd->buffer)[i])
	{
		cmd->str = ft_strappone(cmd->str, (cmd->buffer)[i], j + i);
		i++;
	}
	print_line(cmd);
	i = (int)ft_strlen(cmd->buffer);
	while (i-- > 0)
		go_right(cmd);
}

void			copy_handler(t_cmd *cmd)
{
	char		buf[6];
	int			swap;
	int			start;

	swap = 0;
	start = cmd->col;
	bzero(buf, 6);
	while (buf[0] != -61 && buf[1] != -89)
	{
		bzero(buf, 6);
		read(0, buf, 5);
		core_handler(cmd, buf, &swap, start);
	}
	stock_buffer(cmd, start);
	print_line(cmd);
}

void			copy_cut_paste_handler(t_cmd *cmd, char *macro)
{
	if (macro[0] == -30 && macro[1] == -119 && macro[2] == -120)
		cut_handler(cmd);
	if (macro[0] == -30 && macro[1] == -120 && macro[2] == -102)
		paste_handler(cmd);
	if (macro[0] == -61 && macro[1] == -89 && macro[2] == 0)
		copy_handler(cmd);
}
