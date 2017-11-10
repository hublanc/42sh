/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_isatty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:06:24 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 16:30:55 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		history_isatty(char *search)
{
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr("(reverse-i-search)`");
	ft_putstr(search);
	ft_putstr("': ");
}

void		set_failing(char *search, struct winsize z)
{
	go_begin((ft_strlen(search) + 26), z.ws_col);
	ttyyyy(0) ? tputs(tgetstr("cd", NULL), 1, tputchar) : 0;
	ttyyyy(0) ? ft_putstr("failing reverse-i-search: ") : 0;
	ft_putstr(search);
	if ((26 + ft_strlen(search)) % z.ws_col == 0)
	{
		ttyyyy(0) ? tputs(tgetstr("cr", NULL), 1, tputchar) : 0;
		ttyyyy(0) ? tputs(tgetstr("do", NULL), 1, tputchar) : 0;
	}
}
