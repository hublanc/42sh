/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_tty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:18:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/13 13:49:00 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	test_tty(struct termios term)
{
	char	tmp[6];

	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(0, TCSADRAIN, &term);
	tmp[5] = 0;
	if (!isatty(0))
	{
		tmp[0] = 0;
		if (read(0, tmp, 5) == -1)
			exit(EXIT_FAILURE);
		if (!tmp[0])
			exit(EXIT_FAILURE);
		save_buf(tmp);
		can_sigint(1);
	}
	if (!isatty(1))
		if (read(1, tmp, 0) == -1)
			exit(EXIT_FAILURE);
}

void		check_in(struct termios term)
{
	g_term = term;
	term.c_lflag &= ~(ECHO | ICANON);
	if (!save_buf(NULL))
		test_tty(term);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

int			ttyyyy(int i)
{
	if (i == 0)
		return (isatty(0) && isatty(1));
	if (i == 2)
		return (isatty(0));
	return (1);
}
