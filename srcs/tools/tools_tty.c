/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_tty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:18:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/14 12:57:26 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	test_tty(struct termios term, int i)
{
	char	tmp[6];
	int		ret;

	ret = 0;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(0, TCSADRAIN, &term);
	tmp[5] = 0;
	if (!isatty(0))
	{
		tmp[0] = 0;
		if (read(0, tmp, 5) == -1)
			ret = 1;
		if (!tmp[0])
			ret = 1;
		i == 0 ? save_buf(tmp) : 0;
		i == 0 ? can_sigint(1) : 0;
	}
	if (!isatty(1))
		if (read(1, tmp, 0) == -1)
			ret += 2;
	return (ret);
}

int			check_in(struct termios term, int i)
{
	struct termios	term2;
	int				ret;

	term2 = term;
	ret = 0;
	i == 0 ? term.c_lflag &= ~(ECHO | ICANON) : 0;
	if (!save_buf(NULL))
		ret = test_tty(term2, i);
	tcsetattr(0, TCSADRAIN, &term);
	return (ret);
}

int			ttyyyy(int i)
{
	if (i == 0)
		return (isatty(0) && isatty(1));
	if (i == 2)
		return (isatty(0));
	if (i == 3)
		return (isatty(0) && isatty(2));
	return (1);
}
