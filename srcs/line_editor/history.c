/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 19:01:20 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:42:57 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_hist			*new_history(char *cmd)
{
	t_hist		*new;

	if (!(new = (t_hist*)ft_memalloc(sizeof(struct s_hist))))
		return (NULL);
	if (cmd)
		new->cmd = ft_strdup(cmd);
	new->next = NULL;
	return (new);
}

void			add_begin(t_hist **list, t_hist *new)
{
	if (*list)
		new->next = *list;
	*list = new;
}

void			delone_history(t_hist **list)
{
	if (!list)
		return ;
	ft_strdel(&(*list)->cmd);
	free(*list);
	*list = NULL;
}

void			del_history(t_hist **list)
{
	if (*list)
	{
		del_history(&(*list)->next);
		delone_history(&(*list));
	}
}

void			del_current(t_hist **list)
{
	t_hist		*tmp;

	if (!*list)
		return ;
	if ((*list)->current)
	{
		tmp = *list;
		*list = (*list)->next;
		ft_putstr(tmp->cmd);
		delone_history(&tmp);
	}
}
