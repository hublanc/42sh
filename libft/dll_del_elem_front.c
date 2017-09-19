/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_del_elem_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:20:39 by mameyer           #+#    #+#             */
/*   Updated: 2017/08/30 09:31:15 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

t_control		*dll_del_elem_front(t_control *control)
{
	t_lst		*tmp;

	if (dll_is_empty(control))
		return (control);
	if (control->length == 1 && control->begin == control->end)
	{
		free(control->begin->name);
		free(control);
		return (NULL);
	}
	tmp = control->begin;
	control->begin = control->begin->next;
	control->begin->prev = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	free(tmp->name);
	free(tmp);
	tmp = NULL;
	control->length--;
	return (control);
}
