/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:07:25 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/17 11:41:51 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd		*save_cmd(t_cmd *cmd)
{
	static t_cmd	*s_cmd;

	if (cmd)
		s_cmd = cmd;
	return (s_cmd);
}

t_cmd		init_cmd(char *prompt)
{
	t_cmd	new;

	if (!ft_strcmp(prompt, "dquote> ") || !ft_strcmp(prompt, "quote> ")
	|| !ft_strcmp(prompt, "heredoc> ") || !ft_strcmp(prompt, "pipe> ")
	|| !ft_strcmp(prompt, "> ") || !ft_strcmp(prompt, "cmdandor> "))
		new.prompt = ft_strdup(prompt);
	else
		new.prompt = prompt;
	new.prlen = ft_strlen(prompt);
	new.str = NULL;
	new.str_quote = NULL;
	new.buffer = NULL;
	new.save_cmd = NULL;
	new.eof = NULL;
	new.end_bs = 0;
	new.end_pp = 0;
	new.end_eof = 0;
	new.line = 0;
	new.col = new.prlen + 1;
	new.sc_col = 0;
	new.sc_row = 0;
	new.stop = 0;
	return (new);
}

void		clear_cmd(t_cmd *cmd)
{
	if (cmd->prompt)
		ft_strdel(&(cmd->prompt));
	if (cmd->str)
		ft_strdel(&(cmd->str));
	if (cmd->str_quote)
		ft_strdel(&(cmd->str_quote));
	if (cmd->eof)
		ft_strdel(&(cmd->eof));
	if (cmd->save_cmd)
		ft_strdel(&(cmd->save_cmd));
	if (cmd->buffer)
		ft_strdel(&(cmd->buffer));
}

void		init_screen(t_cmd *cmd)
{
	struct winsize	sc;

	if (ioctl(0, TIOCGWINSZ, &sc) == -1)
	{
		cmd->sc_col = 10;
		cmd->sc_row = 10;
	}
	else
	{
		cmd->sc_col = sc.ws_col;
		cmd->sc_row = sc.ws_row;
	}
}
