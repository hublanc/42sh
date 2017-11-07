/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:11:04 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/07 17:11:06 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_cd_flags_3(t_hist_flags *flags, char c)
{
	if (c == 'r')
	{
		(flags->more)++;
		flags->r = 1;
	}
	else if (c == 'w')
	{
		(flags->more)++;
		flags->w = 1;
	}
	else if (c == 'p')
		flags->p = 1;
	else if (c == 's')
		flags->s = 1;
	else
	{
		set_usage(c, 0);
		return (0);
	}
	return (1);
}
