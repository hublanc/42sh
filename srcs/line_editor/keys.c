/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:41:39 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/18 14:08:03 by amazurie         ###   ########.fr       */
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

void		add_line(t_cmd *cmd, char *buf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4 && (ft_isprint(buf[i]) || buf[i] == 9))
	{
		j = 2;
		if (buf[i] == 9)
			j = -1;
		if (buf[i] == 9)
			buf[i] = ' ';
		while (++j < 4)
		{
			cmd->str = ft_strappone(cmd->str, buf[i],
					(cmd->col - 1) - cmd->prlen);
			print_line(cmd);
			go_right(cmd);
		}
	}
}

static char *save_buf(char *buf)
{
	static char *s_buf = NULL;

	if (buf)
		s_buf = ft_strdup(buf);
	return (s_buf);
}

void		key_handler(t_cmd *cmd, t_hist **history, char ***env)
{
	char			*buf;

	init_screen(cmd);
	if (is_sigint(0))
	{
		if (ft_strcmp(cmd->prompt, return_prompt()))
		{
			reset_cmdsiginted(cmd);
			return ;
		}
		else
		{
			reset_cmdsiginted(cmd);
			cmd->stop = 0;
			is_sigint(0);
		}
		buf = save_buf(NULL);
	}
	else
	{
		buf = (char *)ft_memalloc(5);
		read(0, buf, 4);
	}
	if (is_sigint(0))
	{
		reset_cmdsiginted(cmd);
		save_buf(buf);
		return ;
	}
	if (buf[0] == 27)
		arrow_handler(buf, cmd, history);
	else if (buf[0] == 127 && cmd->col > cmd->prlen + 1)
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		print_line(cmd);
		go_left(cmd);
	}
	else if (buf[0] == 12 && !buf[1])
	{
		tputs(tgetstr("cl", NULL), 1, tputchar);
		print_line(cmd);
	}
	else if (buf[0] == 4 && !buf[1] && (!cmd->str || !cmd->str[0]))
	{
		reset_term();
		exit(EXIT_SUCCESS);
	}
	else if (buf[0] == 10)
		enter_hub(cmd, history, env);
	else if (buf[0] == -30 || buf[0] == -61)
		copy_cut_paste_handler(cmd, buf);
	else
		add_line(cmd, buf);
	free(buf);
}
