/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designators_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:32:01 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/02 19:32:03 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		chevron_designator(t_bang **bang, char **splitted)
{
	int		i;

	if (splitted && !(splitted[1]))
		return (0);
	i = 0;
	while (splitted[1] && splitted[1][i])
	{
		(*bang)->result = ft_str_chr_cat((*bang)->result,
			splitted[1][i]);
		i++;
	}
	return (1);
}