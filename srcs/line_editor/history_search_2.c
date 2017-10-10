/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 18:36:43 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/05 18:36:44 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lst		*move_in_hist(t_lst *pos, char *buf, t_control **history)
{
	if (!pos && history && (*history)->begin)
		pos = (*history)->begin;
	if (buf[2] == 'A' && pos && pos->next)
		pos = pos->next;
	else if (buf[2] == 'B' && pos && pos->prev)
		pos = pos->prev;
	return (pos);
}

void		init_hist_search(char **search, t_lst **tmp)
{
	*search = NULL;
	*tmp = NULL;
	if (!((*search) = (char *)malloc(sizeof(char) * 1)))
		exit(EXIT_FAILURE);
	ft_strclr(*search);
	set_search_prompt(NULL, NULL, 0);
}
