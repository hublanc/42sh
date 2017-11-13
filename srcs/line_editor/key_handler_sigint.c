/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_sigint.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:26:24 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:30:11 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		key_handler_sigint(t_cmd *cmd,
			t_control **history, char ***env, char **buf)
{
	if (!(*buf = (char *)ft_memalloc(6)))
		return ;
	if (!read(0, *buf, 5))
	{
		can_sigint(1);
		while (*buf && (*buf)[0])
		{
			save_buf(*buf);
			key_handler(cmd, history, env);
			*buf = save_buf(NULL);
		}
		if (cmd->str)
			enter_hub(cmd, history, env);
		stop_shell(env, NULL, history);
	}
}
