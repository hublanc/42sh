/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 18:36:43 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/14 12:46:28 by hublanc          ###   ########.fr       */
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
	set_search_prompt(NULL, NULL, 0, 1);
}

char		*return_sigint(char **to_del, char *to_save)
{
	ft_strdel(to_del);
	save_buf(to_save);
	return (NULL);
}

char		*return_sigint_2(char **to_del, char *to_save)
{
	set_lenprev(0);
	can_sigint(1);
	is_sigint(1);
	return (return_sigint(to_del, to_save));
}
