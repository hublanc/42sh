/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_r_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:34:59 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/19 12:08:17 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	read_r_opt2(char **readding, char buf[2])
{
	if (buf[0] == 127 && !buf[1])
	{
		if (*readding)
		{
			tputs(tgetstr("le", NULL), 1, &put_my_char);
			tputs(tgetstr("cd", NULL), 1, &put_my_char);
			(*readding)[ft_strlen(*readding) - 1] = '\0';
		}
	}
	else if (ft_isprint(buf[0]) && !buf[1] && !read_singleton(-1))
	{
		ft_putchar(buf[0]);
		*readding = ft_strapp(*readding, buf);
	}
}

char		*read_r_opt(void)
{
	char	buf[2];
	char	*readding;

	set_terminal();
	readding = ft_strnew(0);
	while (1)
	{
		ft_bzero(buf, 2);
		read(0, buf, 1);
		if (!read_singleton(-1))
		{
			ft_strdel(&readding);
			save_buf(buf);
			can_sigint(1);
			return (NULL);
		}
		else if (buf[0] == 10 || buf[0] == 4)
			break ;
		else
			read_r_opt2(&readding, buf);
	}
	reset_term();
	return (readding);
}
