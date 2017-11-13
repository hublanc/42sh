/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 15:46:37 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 18:44:27 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		core_handler(t_cmd *cmd, char *buf, int *swap, int start)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68
			&& cmd->col > cmd->prlen + 1)
		left_handler(cmd, swap, start);
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67
			&& cmd->col < (int)ft_strlen(cmd->str) + cmd->prlen + 1)
		right_handler(cmd, swap, start);
}

static void		cut_handler(t_cmd *cmd)
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
		if (is_sigint(0))
			return (sigint_ccp(buf));
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

static void		copy_handler(t_cmd *cmd)
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
		if (is_sigint(0))
			return (sigint_ccp(buf));
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
