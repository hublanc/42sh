/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:41:39 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/18 15:30:29 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*save_buf(char *buf)
{
	static char *s_buf = NULL;

	if (buf)
		s_buf = ft_strdup(buf);
	return (s_buf);
}

static int	check_sigint(t_cmd *cmd, char **buf)
{
	if (can_sigint(0) && is_sigint(0))
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
	return (1);
}

static void	handle_key2(t_cmd *cmd, t_control **history, char ***env, char *buf)
{
	if (buf[0] == 10)
		enter_hub(cmd, history, env);
	else if (buf[0] == -30 || buf[0] == -61)
		copy_cut_paste_handler(cmd, buf);
	else if (buf[0] == 18)
	{
		ft_strdel(&cmd->str);
		cmd->col = cmd->prlen + 1;
		cmd->str = history_search(history);
		print_line(cmd);
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
		tputs(tgetstr("cl", NULL), 1, tputchar);
		print_prompt();
		print_line(cmd);
	}
	else if (buf[0] == 4 && !buf[1] && (!cmd->str || !cmd->str[0]))
	{
		reset_term();
		exit(EXIT_SUCCESS);
	}
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
	{
		buf = (char *)ft_memalloc(1000);
		read(0, buf, 999);
	}
	else if (i == -1)
		return ;
	if (buf[0] == 9 && !buf[1] && is_sigint(0) == 0)
		completion(cmd, env, &buf);
	else if (buf[0] == 9 && !buf[1])
		is_sigint(1);
	if (is_sigint(0))
	{
		reset_cmdsiginted(cmd);
		save_buf(buf);
		can_sigint(1);
		free(buf);
		return ;
	}
	handle_key(cmd, history, env, buf);
	(buf) ? free(buf) : 0;
}
