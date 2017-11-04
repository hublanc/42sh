/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 12:52:57 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/04 13:43:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_sigint2(t_cmd *cmd, char **buf)
{
	*buf = return_prompt();
	if (ft_strcmp(cmd->prompt, *buf))
	{
		reset_cmdsiginted(cmd);
		can_sigint(1);
		return (-1);
	}
	else
	{
		reset_cmdsiginted(cmd);
		cmd->stop = 0;
		is_sigint(0);
	}
	(*buf) ? free(*buf) : 0;
	*buf = save_buf(NULL);
	return (0);
}

static int	check_sigint(t_cmd *cmd, char **buf)
{
	int	i;

	if ((i = can_sigint(0)) && is_sigint(0))
		return (check_sigint2(cmd, buf));
	else if (i)
	{
		(*buf) ? free(*buf) : 0;
		if (!(*buf = save_buf(NULL)))
			return (1);
		return (0);
	}
	return (1);
}

static void	handle_key2(t_cmd *cmd, t_control **history, char ***env, char *buf)
{
	struct winsize		z;

	if (buf[0] == 10)
	{
		(buf[1]) ? save_buf(buf + 1) : 0;
		(buf[1]) ? can_sigint(1) : 0;
		enter_hub(cmd, history, env);
	}
	else if (buf[0] == -30 || buf[0] == -61)
		copy_cut_paste_handler(cmd, buf);
	else if (buf[0] == 18)
	{
		if (ioctl(0, TIOCGWINSZ, &z) == -1)
			return ;
		go_begin((ft_strlen(cmd->str) + ft_strlen(cmd->prompt)), z.ws_col);
		isatty(0) ? tputs(tgetstr("cd", NULL), 1, tputchar) : 0;
		ft_strdel(&cmd->str);
		cmd->col = cmd->prlen + 1;
		if (return_void(cmd, history, env))
			return ;
	}
	else
		add_line(cmd, buf);
}

static void	handle_key(t_cmd *cmd, t_control **history, char ***env, char *buf)
{
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
		isatty(0) ? tputs(tgetstr("cl", NULL), 1, tputchar) : 0;
		print_prompt();
		print_line(cmd);
	}
	else if (buf[0] == 4 && !buf[1] && (!cmd->str || !cmd->str[0]))
		stop_shell(env, NULL, history);
	else
		handle_key2(cmd, history, env, buf);
}

void		key_handler(t_cmd *cmd, t_control **history, char ***env)
{
	char	*buf;
	int		i;

	init_screen(cmd);
	buf = NULL;
	if ((i = check_sigint(cmd, &buf)))
		key_handler_sigint(cmd, history, env, &buf);
	else if (i == -1)
		return ;
	if (buf[0] == 9 && !buf[1] && is_sigint(0) == 0)
		while (isatty(0) && buf[0] == 9 && !buf[1])
			completion(cmd, env, &buf);
	else if (buf[0] == 9 && !buf[1])
		is_sigint(1);
	if (is_sigint(0))
	{
		reset_cmdsiginted(cmd);
		save_buf(buf);
		can_sigint(1);
		(buf) ? free(buf) : 0;
		return ;
	}
	handle_key(cmd, history, env, buf);
	(buf) ? free(buf) : 0;
}
