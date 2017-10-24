/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:09:47 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/24 13:12:36 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**		Change history_search return from char * to int
*/

int			history_search(t_control **history, char **str)
{
	char		buf[3];
	char		*search;
	t_lst		*tmp;

	if (!(*history) || (*history && (*history)->length < 1))
		return (0);
	init_hist_search(&search, &tmp);
	ft_strclr(buf);
	while (read(1, &buf, 3))
	{
		if (is_sigint(0))
		{
			can_sigint(1);
			is_sigint(1);
			save_buf(buf);
			return (0);
		}
		if (ft_isprint(buf[0]) || (buf[0] == 127)
			|| (buf[0] == 27 && tmp))
			tmp = while_handler(buf, &search, history, tmp);
		else if (buf[0] != 18)
			break ;
		ft_strclr(buf);
	}
	return (return_handler(tmp, buf, &search, str));
}

int			return_handler(t_lst *tmp, char *buf, char **search, char **str)
{
	if (tmp && buf[0] == 10)
	{
		ft_strdel(search);
		*str = ft_strdup(tmp->name);
		return (1);
	}
	return (1);
}

t_lst		*while_handler(char *buf, char **search, t_control **history,
			t_lst *tmp)
{
	if (ft_isprint(buf[0]))
	{
		*search = ft_str_chr_cat(*search, buf[0]);
		tmp = history_search_2(history, *search);
	}
	else if (buf[0] == 127 && *search && ft_strlen(*search) > 0)
	{
		*search = ft_strdelone(*search, ft_strlen(*search));
		tmp = history_search_2(history, *search);
	}
	else if (buf[0] == 27 && tmp)
		tmp = move_in_hist(tmp, buf, history);
	set_search_prompt(*search, tmp, 1);
	return (tmp);
}

void		set_search_prompt(char *search, t_lst *tmp, int type)
{
	if (type == 0)
	{
		go_begin(0, 0);
		tputs(tgetstr("cd", NULL), 1, tputchar);
		ft_putstr("(reverse-i-search)`': ");
		return ;
	}
	go_begin(0, 0);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr("(reverse-i-search)`");
	ft_putstr(search);
	ft_putstr("': ");
	if (tmp)
		ft_putstr(tmp->name);
	else
	{
		go_begin(0, 0);
		tputs(tgetstr("cd", NULL), 1, tputchar);
		ft_putstr("failing reverse-i-search: ");
		ft_putstr(search);
		ft_putchar('_');
	}
}

t_lst		*history_search_2(t_control **history, char *search)
{
	t_lst	*tmp;

	if (ft_strlen(search) < 1)
		return (NULL);
	tmp = NULL;
	if (history && (*history)->begin)
		tmp = (*history)->begin;
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->name, search) != 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
