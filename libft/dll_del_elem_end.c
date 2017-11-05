/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_del_elem_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:17:50 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/05 13:32:11 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

t_control		*dll_del_elem_end(t_control *control)
{
	t_lst		*tmp;

	if (dll_is_empty(control))
		return (control);
	if (control->length == 1 && control->begin == control->end)
	{
		ft_strdel(&control->begin->name);
		free(control);
		return (NULL);
	}
	tmp = control->end;
	control->end = control->end->prev;
	control->end->next = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	ft_strdel(&tmp->name);
	free(tmp);
	control->length--;
	return (control);
}
