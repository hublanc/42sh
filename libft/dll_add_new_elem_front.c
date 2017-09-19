/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_add_new_elem_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:11:17 by mameyer           #+#    #+#             */
/*   Updated: 2017/08/30 07:46:29 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

t_control		*dll_add_new_elem_frnt(t_control *control, char *value)
{
	t_lst		*elem;

	if (!(elem = malloc(sizeof(t_lst))))
		return (NULL);
	elem->name = ft_strdup(value);
	elem->selected = 0;
	elem->current = 0;
	elem->next = NULL;
	elem->prev = NULL;
	if (dll_is_empty(control))
	{
		if (!(control = malloc(sizeof(t_control))))
			return (NULL);
		control->length = 0;
		control->begin = elem;
		control->end = elem;
	}
	else
	{
		control->begin->prev = elem;
		elem->next = control->begin;
		control->begin = elem;
	}
	control->length++;
	return (control);
}
