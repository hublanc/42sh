/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 19:21:38 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 15:31:25 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lst		*seek_next_select(t_control **list)
{
	t_lst		*tmp;

	tmp = (*list)->begin;
	while (tmp)
	{
		if (tmp->selected == 1 && tmp->next)
		{
			tmp->selected = 0;
			tmp->next->selected = 1;
			return (tmp->next);
		}
		else if (tmp->selected == 1 && !tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		seek_next(t_control **list, t_cmd *cmd)
{
	t_lst		*tmp;

	if (!(*list) || !cmd)
		return ;
	tmp = seek_next_select(list);
	if (!tmp)
	{
		tmp = (*list)->begin;
		tmp->selected = 1;
		ft_strdel(&(cmd->save_cmd));
		cmd->save_cmd = ft_strdup(cmd->str);
		(*list)->begin->current = 1;
	}
	change_cmd(tmp->name, cmd);
}

t_lst		*seek_prev_select(t_control **list)
{
	t_lst		*tmp;

	if (!list)
		return (NULL);
	tmp = (*list)->begin;
	while (tmp->next)
	{
		if (tmp->next->selected == 1)
		{
			tmp->next->selected = 0;
			tmp->selected = 1;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void		seek_prev(t_control **list, t_cmd *cmd)
{
	t_lst		*tmp;

	if (*list == NULL)
		return ;
	tmp = seek_prev_select(list);
	if (!tmp)
	{
		if ((*list)->begin->selected == 1)
			change_cmd(cmd->save_cmd, cmd);
		(*list)->begin->selected = 0;
		return ;
	}
	change_cmd(tmp->name, cmd);
}
