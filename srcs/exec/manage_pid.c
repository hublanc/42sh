/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 14:19:59 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/12 15:21:18 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_pidp			**singleton_pid(void)
{
	static t_pidp		*s_pid = NULL;

	return (&s_pid);
}

void			fetch_pid(pid_t pid)
{
	t_pidp			**list;

	list = singleton_pid();
	add_pid(list, new_pid(pid));
}

void			wait_allpid(void)
{
	t_pidp			**list;
	t_pidp			*tmp;
	int				*status;

	status = singleton_status();
	list = singleton_pid();
	tmp = *list;
	while (tmp)
	{
		waitpid(tmp->pid, status, WUNTRACED | WCONTINUED);
		tmp = tmp->next;
	}
	del_pid(list);
}
