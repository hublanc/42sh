/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:23:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/12 13:26:05 by lbopp            ###   ########.fr       */
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
			ft_putstr(tmp->name);
			ft_putchar(sep);
			tmp = tmp->next;
		}
	}
}
