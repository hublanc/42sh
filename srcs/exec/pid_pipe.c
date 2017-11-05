/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:07:48 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/12 14:43:16 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_pidp			*new_pid(pid_t pid)
{
	t_pidp		*new;

	if (!(new = (t_pidp*)ft_memalloc(sizeof(struct s_pidp))))
		return (NULL);
	new->pid = pid;
	new->next = NULL;
	return (new);
}

void			add_pid(t_pidp **list, t_pidp *new)
{
	if (*list)
	{
		while (*list)
			list = &(*list)->next;
		*list = new;
	}
	else
		*list = new;
}

void			delone_pid(t_pidp **list)
{
	if (!list)
		return ;
	free(*list);
	*list = NULL;
}

void			del_pid(t_pidp **list)
{
	if (*list)
	{
		del_pid(&(*list)->next);
		delone_pid(&(*list));
	}
}
