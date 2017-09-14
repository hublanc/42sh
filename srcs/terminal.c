/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:40:20 by hublanc           #+#    #+#             */
/*   Updated: 2017/08/23 15:59:28 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		set_terminal(void)
{
	char			*name_term;
	struct termios	term;

	name_term = getenv("TERM");
	if (!name_term || !*name_term)
	{
		ft_putstr_fd("TERM not found\n", 2);
		exit(EXIT_FAILURE);
	}
	if (tgetent(NULL, name_term) == -1)
	{
		ft_putstr_fd("TERM invalid\n", 2);
		exit(EXIT_FAILURE);
	}
	tcgetattr(0, &term);
	g_term = term;
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void		reset_term(void)
{
	/*struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSADRAIN, &term);*/
	tcsetattr(0, TCSADRAIN, &g_term);
}

void		reset_disp(void)
{
	tputs(tgetstr("cl", NULL), 1, tputchar);
}

int			tputchar(int c)
{
	write(1, &c, 1);
	return (c);
}
