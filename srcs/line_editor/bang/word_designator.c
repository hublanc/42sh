/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:29:08 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 20:17:48 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_ydigit(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i])
		return (i);
	bang->y = ft_atoi(cmd + i);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	return (i);
}

int			word_designator_y(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i] || cmd[i] != '-' || bang->dash == 1)
		return (i);
	i++;
	bang->dash = 1;
	if (cmd[i] && cmd[i] == '^')
		bang->c_y = '^';
	else if (cmd[i] && cmd[i] == '$')
		bang->c_y = '$';
	else if (cmd[i] && cmd[i] == '*')
		bang->c_y = '*';
	else if (cmd[i] && ft_isdigit(cmd[i]))
		i = get_ydigit(cmd, bang, i);
	return (i);
}

int			get_xdigit(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i])
		return (i);
	bang->x = ft_atoi(cmd + i);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	if (cmd[i] && cmd[i] == '*')
	{
		bang->dash = 1;
		bang->c_y = '*';
	}
	return (i);
}

int			word_designator_x(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i] || cmd[i] != ':')
		return (i);
	i++;
	if (cmd[i] && cmd[i] == '^')
		bang->c_x = '^';
	else if (cmd[i] && cmd[i] == '$')
		bang->c_x = '$';
	else if (cmd[i] && cmd[i] == '*')
		bang->c_x = '*';
	else if (cmd[i] && ft_isdigit(cmd[i]))
		i = get_xdigit(cmd, bang, i);
	return (i);
}