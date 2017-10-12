/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:41:39 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 17:41:27 by hublanc          ###   ########.fr       */
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
	|| !ft_strcmp(cmd->prompt, "> ") || !ft_strcmp(cmd->prompt, "cmdandor> "))
		ft_putstr(cmd->prompt);
	else
		print_prompt();
}

void		pass_prompt(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < cmd->prlen)
	{
		if (i == cmd->sc_col)
			go_down();
		else
			tputs(tgetstr("nd", NULL), 1, tputchar);
		i++;
	}
}

void		print_line(t_cmd *cmd)
{
	int		len;

	len = cmd->prlen + (int)ft_strlen(cmd->str);
	len += len % cmd->sc_col == 0 ? 0 : 1;
	go_begin(cmd->col, cmd->sc_col);
	pass_prompt(cmd);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	//choose_prompt(cmd);
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
	int	k;

	signal(SIGINT, &signal_do_nothing);
	i = -1;
	k = 0;
	while (buf && (size_t)++i < ft_strlen(buf) && buf[i] && (ft_isprint(buf[i])
				|| buf[i] == 9))
	{
		j = 2;
		if (buf[i] == 9)
			j = -1;
		if (buf[i] == 9)
			buf[i] = ' ';
		while (++j < 4)
		{
			cmd->str = ft_strappone(cmd->str, buf[i],
					(cmd->col + k - 1) - cmd->prlen);
			k++;
		}
	}
	print_line(cmd);
	while (k--)
		go_right(cmd);
	signal(SIGINT, &get_signal);
}

static char *save_buf(char *buf)
{
	static char *s_buf = NULL;

	if (buf)
		s_buf = ft_strdup(buf);
	return (s_buf);
}

void		key_handler(t_cmd *cmd, t_control **history, char ***env)
{
	char			*buf;

	init_screen(cmd);
	if (can_sigint(0) && is_sigint(0))
	{
		buf = return_prompt();
		if (ft_strcmp(cmd->prompt, buf))
		{
			reset_cmdsiginted(cmd);
			can_sigint(1);
			return ;
		}
		else
		{
			reset_cmdsiginted(cmd);
			cmd->stop = 0;
			is_sigint(0);
		}
		(buf) ? free(buf) : 0;
		buf = save_buf(NULL);
	}
	else
	{
		buf = (char *)ft_memalloc(1000);
		read(0, buf, 999);
	}
	if (is_sigint(0))
	{
		reset_cmdsiginted(cmd);
		save_buf(buf);
		can_sigint(1);
		free(buf);
		return ;
	}
	if (buf[0] == 9 && !buf[1])
		completion(cmd, env, &buf);
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
	else if (buf[0] == 18)	// CTRL + R
	{
		ft_strdel(&cmd->str);
		cmd->col = cmd->prlen + 1;
		cmd->str = history_search(history);
		print_line(cmd);
	}
	else
		add_line(cmd, buf);
	(buf) ? free(buf) : 0;
}
