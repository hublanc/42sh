/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_clear_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:25:47 by mameyer           #+#    #+#             */
/*   Updated: 2017/08/30 06:30:12 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

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
