/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_isatty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:06:24 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 16:24:28 by hublanc          ###   ########.fr       */
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

void		go_up_ctrlr(struct winsize z)
{
	int		wcol;

	wcol = z.ws_col;
	ttyyyy(0) ? tputs(tgetstr("up", NULL), 1, tputchar) : 0;
	while (wcol-- > 0)
		ttyyyy(0) ? tputs(tgetstr("nd", NULL), 1, tputchar) : 0;
}

void		go_down_ctrlr(void)
{
	ttyyyy(0) ? tputs(tgetstr("cr", NULL), 1, tputchar) : 0;
	ttyyyy(0) ? tputs(tgetstr("do", NULL), 1, tputchar) : 0;
}

void		set_failing(char *search, struct winsize z, int mode)
{
	if ((26 + ft_strlen(search)) % z.ws_col == 0 && !mode)
		go_up_ctrlr(z);
	go_begin((ft_strlen(search) + 26 + return_lenprev()), z.ws_col);
	set_lenprev(0);
	ttyyyy(0) ? tputs(tgetstr("cd", NULL), 1, tputchar) : 0;
	ttyyyy(0) ? ft_putstr("failing reverse-i-search: ") : 0;
	ft_putstr(search);
	if ((26 + ft_strlen(search)) % z.ws_col == 0 && mode)
		go_down_ctrlr();
}
