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

/*
**	BUGS :
**	Chercher une commande dans l'hist puis faire ctrl + R
**	Puis, appuyer sur n'importe quelle touche (autre que les lettres) pour
**	quitter la recherche => Espaces correspondant a la commande tapee avant
**	la recherche
*/

char		*history_search(t_control **history)
{
	char		buf[3];
	char		*search;
	t_lst		*tmp;

	if (!(*history) || (*history && (*history)->length < 1))
		return (NULL);
	init_hist_search(&search, &tmp);
	ft_strclr(buf);
	while (read(1, &buf, 3))
	{
		if (ft_isprint(buf[0]) || (buf[0] == 127 && ft_strlen(search) > 0)
			|| (buf[0] == 27 && tmp))
			tmp = while_handler(buf, &search, history, tmp);
		else
			break ;
		ft_strclr(buf);
	}
	if (tmp)
	{
		ft_strdel(&search);
		return (ft_strdup(tmp->name));
	}
	else
		return (NULL);
}

t_lst		*while_handler(char *buf, char **search, t_control **history,
			t_lst *tmp)
{
	if (ft_isprint(buf[0]))
	{
		*search = ft_str_chr_cat(*search, buf[0]);
		tmp = history_search_2(history, *search);
	}
	else if (buf[0] == 127 && ft_strlen(*search) > 0)
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
