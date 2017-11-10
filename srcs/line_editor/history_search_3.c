/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 21:11:19 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/10 21:11:20 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lst		*while_handler(char *buf, char **search, t_control **history,
			t_lst *tmp)
{
	if (ft_isprint(buf[0]))
	{
		*search = ft_str_chr_cat(*search, buf[0]);
		tmp = history_search_2(history, *search);
		set_search_prompt(*search, tmp, 1);
	}
	else if (buf[0] == 127 && *search && ft_strlen(*search) <= 1)
	{
		tmp = NULL;
		if (ft_strlen(*search) == 1)
			*search = ft_strdelone(*search, ft_strlen(*search));
		set_search_prompt(*search, tmp, 0);
	}
	else if (buf[0] == 127 && *search && ft_strlen(*search) > 1)
	{
		*search = ft_strdelone(*search, ft_strlen(*search));
		tmp = history_search_2(history, *search);
		set_search_prompt(*search, tmp, 1);
	}
	else if (buf[0] == 27 && tmp)
	{
		tmp = move_in_hist(tmp, buf, history);
		set_search_prompt(*search, tmp, 1);
	}
	return (tmp);
}

void		set_search_prompt_2(char *search, t_lst *tmp, struct winsize z)
{
	if (ttyyyy(0))
	{
		go_begin((ft_strlen(search) + 22 + return_lenprev()), z.ws_col);
		history_isatty(search);
	}
	(tmp && ttyyyy(0)) ? ft_putstr(tmp->name) : 0;
	tmp ? set_lenprev(ft_strlen(tmp->name)) : 0;
	if (tmp && (22 + ft_strlen(tmp->name) + ft_strlen(search)) % z.ws_col == 0)
	{
		ttyyyy(0) ? tputs(tgetstr("cr", NULL), 1, tputchar) : 0;
		ttyyyy(0) ? tputs(tgetstr("do", NULL), 1, tputchar) : 0;
	}
	if (tmp)
		return ;
	if (!ttyyyy(0))
		return ;
	set_failing(search, z);
}

void		set_search_prompt(char *search, t_lst *tmp, int type)
{
	struct winsize		z;
	int					len;

	if (tmp)
		len = ft_strlen(tmp->name);
	else
		len = 0;
	if (ioctl(0, TIOCGWINSZ, &z) == -1)
		return ;
	if (type == 0)
	{
		go_begin((ft_strlen(search) + 22 + return_lenprev()), z.ws_col);
		ttyyyy(0) ? tputs(tgetstr("cd", NULL), 1, tputchar) : 0;
		ttyyyy(0) ? ft_putstr("(reverse-i-search)`': ") : 0;
		return ;
	}
	set_search_prompt_2(search, tmp, z);
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
