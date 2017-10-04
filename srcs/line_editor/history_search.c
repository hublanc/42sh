/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:09:47 by mameyer           #+#    #+#             */
/*   Updated: 2017/09/18 15:09:49 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*history_search(t_control **history)
{
	char		buf[3];
	char		*search;
	char		*result;
	t_lst		*tmp;
	int			a;

	search = NULL;
	result = NULL;
	tmp = NULL;
	a = 0;
	if (!(search = (char *)malloc(sizeof(char) * 1)))
		exit(EXIT_FAILURE);
	ft_strclr(search);
	set_search_prompt(NULL, NULL, 0);
	ft_strclr(buf);
	while (read(1, &buf, 3))
	{
		if (ft_isprint(buf[0]) && (a = 1))
			add_and_search(&search, &tmp, history, buf);
		else if (buf[0] == 127 && ft_strlen(search) > 0 && a != 0)
			del_and_search(&search, &tmp, history);
		else if (buf[0] == 27 && a == 0)
		{
			if (buf[2] == 'A')
				return (ft_strdup((*history)->begin->name));
		}
		else if (buf[0] == 27)
			tmp = move_in_hist(tmp, buf);
		else if (buf[0] == 10)
		{
			ft_strdel(&search);
			if (tmp != NULL)
				result = ft_strdup(tmp->name);
			go_begin(0, 0);
			tputs(tgetstr("cd", NULL), 1, tputchar);
			return (result);
		}
		set_search_prompt(search, tmp, 1);
		ft_strclr(buf);
	}
	return (NULL);
}

void		del_and_search(char **search, t_lst **tmp, t_control **history)
{
	(*search) = ft_strdelone(*search, ft_strlen(*search));
	(*tmp) = history_search_2(history, *search);
}

void		add_and_search(char **search, t_lst **tmp, t_control **history, char *buf)
{
	(*search) = ft_str_chr_cat(*search, buf[0]);
	(*tmp) = history_search_2(history, *search);
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
	if (tmp != NULL)
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
		if (ft_strlen(tmp->name) >= ft_strlen(search)
			&& ft_strstr(tmp->name, search) != 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_lst		*move_in_hist(t_lst *pos, char *buf)
{
	if (buf[2] == 'A' && pos && pos->next)
		pos = pos->next;
	else if (buf[2] == 'B' && pos && pos->prev)
		pos = pos->prev;
	return (pos);
}