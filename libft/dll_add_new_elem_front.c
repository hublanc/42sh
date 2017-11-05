/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_add_new_elem_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:11:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/08/30 07:46:29 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

static void		init_elem(t_lst **elem)
{
	(*elem)->selected = 0;
	(*elem)->current = 0;
	(*elem)->next = NULL;
	(*elem)->prev = NULL;
}

t_control		*dll_add_new_elem_frnt(t_control *control, char *value)
{
	t_lst		*elem;

	if (!(elem = malloc(sizeof(t_lst))))
		return (NULL);
	elem->name = ft_strdup(value);
	init_elem(&elem);
	if (dll_is_empty(control))
	{
		if (!(control = malloc(sizeof(t_control))))
			return (NULL);
		control->length = 0;
		control->original_length = 0;
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
