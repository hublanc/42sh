/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_wd_designators_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 20:01:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/02 20:01:08 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		which_char_after_digit(t_bang **bang)
{
	int		i;

	i = (*bang)->index;
	if (!((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]))
		return (0);
	while (i < (*bang)->len && (*bang)->command[i]
		&& ft_isdigit((*bang)->command[i]))
		i++;
	return ((*bang)->command[i]);
}
