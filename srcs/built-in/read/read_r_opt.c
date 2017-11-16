/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_r_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:34:59 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 10:44:19 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	read_r_opt2(char **readding, char buf[6])
{
	int		i;
	char	tmp[2];

	if (buf[0] == 127 && !buf[1])
	{
		if (*readding)
		{
			tputs(tgetstr("le", NULL), 1, &tputchar);
			tputs(tgetstr("cd", NULL), 1, &tputchar);
			(*readding)[ft_strlen(*readding) - 1] = '\0';
		}
		return ;
	}
	i = 0;
	while (buf[i] && ft_isprint(buf[i]))
	{
		tmp[1] = '\0';
		tmp[0] = buf[i];
		*readding = ft_strapp(*readding, tmp);
		ft_putchar(buf[i]);
		i++;
	}
}

char		*read_r_opt(void)
{
	char	buf[6];
	char	*readding;

	set_terminal();
	readding = ft_strnew(0);
	while (1)
	{
		ft_bzero(buf, 6);
		read(0, buf, 5);
		if (!read_singleton(-1))
		{
			ft_strdel(&readding);
			save_buf(buf);
			can_sigint(1);
			return (NULL);
		}
		else if (buf[0] == 10 || buf[0] == 4)
			break ;
		else if (readding)
			read_r_opt2(&readding, buf);
	}
	reset_term();
	return (readding);
}
