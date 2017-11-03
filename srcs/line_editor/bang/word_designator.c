/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:29:08 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 16:01:20 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*get_ydigit(char *cmd, t_bang2 *bang)
{
	if (!cmd || !*cmd)
		return (cmd);
	bang->y = ft_atoi(cmd);
	while (*cmd && ft_isdigit(*cmd))
		cmd++;
	return (cmd);
}

char		*word_designator_y(char *cmd, t_bang2 *bang)
{
	if (!cmd || !*cmd || *cmd != '-' || bang->dash == 1)
		return (cmd);
	cmd++;
	bang->dash = 1;
	if (*cmd && *cmd == '^')
		bang->c_y = '^';
	else if (*cmd && *cmd == '$')
		bang->c_y = '$';
	else if (*cmd && *cmd == '*')
		bang->c_y = '*';
	else if (*cmd && ft_isdigit(*cmd))
		cmd = get_ydigit(cmd, bang);
	return (cmd);
}

char		*get_xdigit(char *cmd, t_bang2 *bang)
{
	if (!cmd || !*cmd)
		return (cmd);
	bang->x = ft_atoi(cmd);
	while (*cmd && ft_isdigit(*cmd))
		cmd++;
	if (*cmd && *cmd == '*')
	{
		bang->dash = 1;
		bang->c_y = '*';
	}
	return (cmd);
}

char		*word_designator_x(char *cmd, t_bang2 *bang)
{
	if (!cmd || !*cmd || *cmd != ':')
		return (cmd);
	cmd++;
	if (*cmd && *cmd == '^')
		bang->c_x = '^';
	else if (*cmd && *cmd == '$')
		bang->c_x = '$';
	else if (*cmd && *cmd == '*')
		bang->c_x = '*';
	else if (*cmd && ft_isdigit(*cmd))
		cmd = get_xdigit(cmd, bang);
	return (cmd);
}
