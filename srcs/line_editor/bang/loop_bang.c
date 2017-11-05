/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:53:11 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/05 15:54:27 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*loop_bang(t_control **history, char *cmd, char ***env)
{
	int		end;
	char	*new;
	t_cmd	cmd2;

	end = 0;
	cmd2 = init_cmd(return_prompt());
	cmd2.str = ft_strdup(cmd);
	while ((new = deal_bang(cmd2.str, *history, &end)) && !end)
	{
		ft_strdel(&cmd2.str);
		cmd2.str = ft_strdup(new);
		enter_hub(&cmd2, history, env);
		ft_strdel(&new);
		clear_cmd(&cmd2);
		tputs(tgetstr("cr", NULL), 1, tputchar);
		return (NULL);
	}
	clear_cmd(&cmd2);
	return (new);
}
