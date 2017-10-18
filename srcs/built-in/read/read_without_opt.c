/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_without_opt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:38:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/18 14:01:55 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	treatment_read_key2(char buf[2], int *backslash, char **readding)
{
	if (buf[0] == '\\')
	{
		ft_putchar(buf[0]);
		if (!(*backslash))
			*backslash = 1;
		else
			*readding = ft_strapp(*readding, buf);
	}
	else if (ft_isprint(buf[0]) && !buf[1] && read_singleton(-1))
	{
		*backslash = 0;
		ft_putchar(buf[0]);
		*readding = ft_strapp(*readding, buf);
	}
}

static int	treatment_read_key(char buf[2], int *backslash, char **readding)
{
	if ((buf[0] == 10 || buf[0] == 4) && !(*backslash))
		return (1);
	else if (buf[0] == 10 && *backslash)
	{
		ft_putstr_fd("\n> ", 2);
		*backslash = 0;
	}
	else if (buf[0] == 127 && !buf[1])
	{
		if (*readding)
		{
			tputs(tgetstr("le", NULL), 1, &put_my_char);
			tputs(tgetstr("cd", NULL), 1, &put_my_char);
			(*readding)[ft_strlen(*readding) - 1] = '\0';
		}
	}
	else
		treatment_read_key2(buf, backslash, readding);
	return (0);
}

char		*read_without_opt(void)
{
	char	*readding;
	char	buf[2];
	int		backslash;

	backslash = 0;
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
		if (treatment_read_key(buf, &backslash, &readding))
			break ;
	}
	reset_term();
	return (readding);
}
