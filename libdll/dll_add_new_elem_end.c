/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_add_new_elem_end.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:14:49 by mameyer           #+#    #+#             */
/*   Updated: 2017/08/30 07:46:22 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

t_control		*dll_add_new_elem_end(t_control *control, char *value)
{
	t_lst		*elem;

	if (!(elem = malloc(sizeof(t_lst))))
		return (NULL);
	elem->name = ft_strdup(value);
	elem->type = 0;
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
		control->end->next = elem;
		elem->prev = control->end;
		control->end = elem;
	}
	control->length++;
	return (control);
}
