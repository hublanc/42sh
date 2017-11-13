/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:07:25 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:17:24 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_cmd		*save_cmd(t_cmd *cmd)
{
	static t_cmd	*s_cmd;
	t_cmd			*tmpcmd;

	if (cmd)
		s_cmd = cmd;
	else
	{
		tmpcmd = s_cmd;
		s_cmd = NULL;
		return (tmpcmd);
	}
	return (s_cmd);
}

static void	init_pr(t_cmd *cmd)
{
	cmd->pr_quote = 0;
	cmd->pr_bs = 0;
	cmd->pr_andor = 0;
	cmd->pr_pipe = 0;
	cmd->pr_here = 0;
	cmd->stop = 0;
}

t_cmd		init_cmd(char *prompt)
{
	t_cmd	new;

	if (!prompt)
		new.prompt = NULL;
	new.prompt = prompt;
	new.prlen = ttyyyy(2) ? strlen_prompt(prompt) : 0;
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
	init_pr(&new);
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
		cmd->sc_col = 100;
		cmd->sc_row = 100;
	}
	else
	{
		cmd->sc_col = sc.ws_col;
		cmd->sc_row = sc.ws_row;
	}
}
