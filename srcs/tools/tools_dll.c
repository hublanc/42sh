/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_dll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:44:31 by mameyer           #+#    #+#             */
/*   Updated: 2017/09/18 18:44:32 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				dll_is_empty(t_control *control)
{
	if (control == NULL)
		return (1);
	return (0);
}

t_control		*dll_add_new_elem_frnt(t_control *control, char *value)
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
		control->begin->prev = elem;
		elem->next = control->begin;
		control->begin = elem;
	}
	control->length++;
	return (control);
}

t_control		*dll_clear_list(t_control *control)
{
	t_lst		*tmp;
	t_lst		*del;

	if (dll_is_empty(control))
		return (control);
	if (control->length == 1 && control->begin == control->end)
	{
		free(control->begin->name);
		free(control);
		control = NULL;
	}
	else
	{
		tmp = control->begin;
		while (tmp != NULL)
		{
			del = tmp;
			tmp = tmp->next;
			free(del->name);
			free(del);
			del = NULL;
		}
		free(control);
	}
	return (control);
}
