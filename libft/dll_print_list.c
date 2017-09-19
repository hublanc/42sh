/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:23:53 by mameyer           #+#    #+#             */
/*   Updated: 2017/08/30 06:30:57 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdll.h"

void		dll_print_list(t_control *control, char sep)
{
	t_lst		*tmp;

	if (dll_is_empty(control))
		return ;
	else
	{
		tmp = control->begin;
		while (tmp != NULL)
		{
		//	ft_putnbr(tmp->type);	// DEBUG
		//	ft_putchar('\t');		// DEBUG
			ft_putstr(tmp->name);
			ft_putchar(sep);
			tmp = tmp->next;
		}
	}
}
