/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:41:39 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/14 13:22:06 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		go_down()
{
	tputs(tgetstr("cr", NULL), 1, tputchar);
	tputs(tgetstr("do", NULL), 1, tputchar);
}

void		choose_prompt(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->prompt, "dquote> ") || !ft_strcmp(cmd->prompt, "quote> ")
	|| !ft_strcmp(cmd->prompt, "heredoc> ") || !ft_strcmp(cmd->prompt, "pipe> ")
	|| !ft_strcmp(cmd->prompt, "> "))
		ft_putstr(cmd->prompt);
	else
		print_prompt();
}

void		print_line(t_cmd *cmd)
{
	int		len;

	len = cmd->prlen + (int)ft_strlen(cmd->str);
	len += len % cmd->sc_col == 0 ? 0 : 1; 
	go_begin(cmd->col, cmd->sc_col);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	choose_prompt(cmd);
	ft_putstr(cmd->str);
	if (len > cmd->col)
	{
		while (len-- != cmd->col)
			tputs(tgetstr("le", NULL), 1, tputchar);
	}
	else if (len < cmd->col)
	{
		while (len != cmd->col)
		{
			if (len % cmd->sc_col == 0)
				go_down();
			else
				tputs(tgetstr("nd", NULL), 1, tputchar);
			len++;
		}
	}
}

void		key_handler(t_cmd *cmd, t_hist **history, char ***env)
{
	char			buf[6];

	init_screen(cmd);
	bzero(buf, 6);
	read(0, buf, 5);
	if (buf[0] == 27)
		arrow_handler(buf, cmd, history);
	else if (buf[0] == 127 && cmd->col > cmd->prlen + 1)
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		print_line(cmd);
		go_left(cmd);
	}
	else if (buf[0] == 10)
		enter_hub(cmd, history, env);
	else if (buf[0] == -30 || buf[0] == -61)
		copy_cut_paste_handler(cmd, buf);
	else if (ft_isprint(buf[0]))
	{
		cmd->str = ft_strappone(cmd->str, buf[0], (cmd->col - 1) - cmd->prlen);
		print_line(cmd);
		go_right(cmd);
	}
	else if (buf[0] == 18)	// CTRL + R
	{
		history_search(history, cmd, env);
	}
}
