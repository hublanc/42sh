/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:32:42 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 13:36:46 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		get_bang_str(char *cmd, t_bang2 *bang, int i)
{
	while (cmd && cmd[i] && cmd[i] != ':' && cmd[i] != ' '
		&& cmd[i] != '!')
	{
		bang->str = ft_str_chr_cat(bang->str, cmd[i]);
		i++;
	}
	return (i);
}

int				event_designator(char *cmd, t_bang2 *bang, int i)
{
	i++;
	if (!cmd || !cmd[i])
		return (i);
	if (cmd[i] == '!' && i++)
		bang->d_bang = 1;
	else if (cmd[i] && (ft_isdigit(cmd[i]) || cmd[i] == '-'))
	{
		bang->cmd_l = ft_atoi(cmd + i);
		bang->n_neg = cmd[i] && cmd[i] == '-' ? 1 : 0;
		cmd[i] && cmd[i] == '-' ? i++ : 0;
		bang->n_set = 1;
		while (cmd[i] && ft_isdigit(cmd[i]))
			i++;
	}
	else if (cmd[i] == '#' && i++)
		bang->hash_t = 1;
	else if (cmd[i] == '?')
	{
		bang->q_mark = 1;
		i++;
		i = get_bang_str(cmd, bang, i);
	}
	else if (cmd[i])
		i = get_bang_str(cmd, bang, i);
	return (i);
}
