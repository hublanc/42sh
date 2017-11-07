/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 17:36:47 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 17:13:13 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	go_down(void)
{
	if (!ttyyyy(0))
		return ;
	tputs(tgetstr("cr", NULL), 1, tputchar);
	tputs(tgetstr("do", NULL), 1, tputchar);
}

void		choose_prompt(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->prompt, "dquote> ")
			|| !ft_strcmp(cmd->prompt, "quote> ")
	|| !ft_strcmp(cmd->prompt, "heredoc> ") || !ft_strcmp(cmd->prompt, "pipe> ")
	|| !ft_strcmp(cmd->prompt, "> ") || !ft_strcmp(cmd->prompt, "cmdandor> "))
		ttyyyy(2) ? ft_putstr_fd(cmd->prompt, 2) : 0;
	else
		ttyyyy(2) ? print_prompt() : 0;
}

static void	pass_prompt(t_cmd *cmd)
{
	int		i;

	if (!isatty(2) || !ttyyyy(2))
		return ;
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

	if (!ttyyyy(0))
		return ;
	len = cmd->prlen + (int)ft_strlen(cmd->str);
	if (!len)
		return ;
	len += len % cmd->sc_col == 0 ? 0 : 1;
	go_begin(cmd->col, cmd->sc_col);
	pass_prompt(cmd);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr(cmd->str);
	if (len > cmd->col)
		while (len-- != cmd->col)
			tputs(tgetstr("le", NULL), 1, tputchar);
	else if (len < cmd->col)
		while (len != cmd->col && len > 0)
		{
			if (len % cmd->sc_col == 0)
				go_down();
			else
				tputs(tgetstr("nd", NULL), 1, tputchar);
			len++;
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
			cmd->str = ft_strappone(cmd->str, buf[i],
					(cmd->col + k++ - 1) - cmd->prlen);
	}
	print_line(cmd);
	while (k--)
		go_right(cmd);
	i > 0 && buf[i] ? save_buf(buf + i) : 0;
	i > 0 && buf[i] ? can_sigint(1) : 0;
	signal(SIGINT, &get_signal);
}
