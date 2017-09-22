/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:00:36 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 17:53:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	add_argtoline(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*args;

	args = &compl->args;
	while (args && compl->curr != args->id)
		args = args->next;
	if (args && args->arg)
		add_line(cmd, args->arg + ft_strlen(compl->arg));
}

static int	check_onscreen(t_compl *compl, int *size, int toskip)
{
	int	i;

	i = -1;
	while (++i < size[3])
	{
		if (compl->curr >= toskip + size[4] * i
				&& compl->curr < toskip + size[4] * i + size[1])
			return (1);
	}
	return (0);
}

static void	get_onscreen(t_compl *compl, t_cmd *cmd)
{
	int	*size;
	int	toskip;
	int	i;

	size = get_size(compl, cmd);
	toskip = compl->toskip;
	while (toskip < size[4] - size[1]
			&& (i = check_onscreen(compl, size, toskip) == 0))
		toskip++;
	if (i > 0)
	{
		compl->toskip = toskip;
		return ;
	}
	while (toskip > 0 && !check_onscreen(compl, size, toskip))
		toskip--;
	compl->toskip = toskip;
}

int		compl_keys(t_compl *compl, t_cmd *cmd, char **buf)
{
	ft_bzero(*buf, ft_strlen(*buf));
	read(0, *buf, 999);
	if ((*buf)[0] == 27 && !(*buf)[1])
		return (-1);
	else if ((*buf)[0] == 27 && compl_arrow(compl, cmd, *buf))
	{
		get_onscreen(compl, cmd);
		display_args(compl, cmd);
	}
	else if ((*buf)[0] == 9 && !(*buf)[1])
	{
		compl->curr = (compl->curr < compl->nbrargs - 1) ? compl->curr + 1 : 0;
		get_onscreen(compl, cmd);
		display_args(compl, cmd);
	}
	else if ((*buf)[0] == 10 && !(*buf)[1])
	{
		add_argtoline(compl, cmd);
		return (-1);
	}
	else
		return (0);
	return (1);
}
