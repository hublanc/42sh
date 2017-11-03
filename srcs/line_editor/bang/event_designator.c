/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:32:42 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 16:06:12 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*get_bang_str(char *cmd, t_bang2 *bang)
{
	while (cmd && *cmd && *cmd != ':' && *cmd != ' ' && *cmd != '!')
	{
		bang->str = ft_str_chr_cat(bang->str, *cmd);
		cmd++;
	}
	return (cmd);
}

char			*event_designator(char *cmd, t_bang2 *bang)
{
	cmd++;
	if (!cmd || !*cmd)
		return (cmd);
	if (*cmd == '!' && cmd++)
		bang->d_bang = 1;
	else if (*cmd && (ft_isdigit(*cmd) || *cmd == '-'))
	{
		bang->cmd_l = ft_atoi(cmd);
		bang->n_set = 1;
		*cmd && *cmd == '-' ? cmd++ : 0;
		while (*cmd && ft_isdigit(*cmd))
			cmd++;
	}
	else if (*cmd == '#' && cmd++)
		bang->hash_t = 1;
	else if (*cmd == '?')
	{
		bang->q_mark = 1;
		cmd++;
		cmd = get_bang_str(cmd, bang);
	}
	else if (*cmd)
		cmd = get_bang_str(cmd, bang);
	return (cmd);
}
