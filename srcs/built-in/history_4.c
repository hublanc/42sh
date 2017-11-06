/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:22:29 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/06 01:04:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				get_cd_flags(t_hist_flags *flags, char **tab, int *args_pos)
{
	int		i;
	int		j;

	i = 1;
	while (tab[i] && tab[i][0] == '-')
	{
		j = 0;
		if (tab[i][j] && tab[i][j] == '-' && tab[i][j + 1])
		{
			j++;
			while (tab[i] && tab[i][j])
				if (get_cd_flags_2(flags, tab[i][j++]))
					return (1);
		}
		else if (tab[i][j] && tab[i][j] == '-' && !(tab[i][j + 1]))
			ft_putendl("shell: history: -: numeric argument required");
		i++;
	}
	*args_pos = i;
	return (0);
}

static int	error_muchflags(void)
{
	ft_putendl("shell: history: cannot use more than one of -anrw");
	return (1);
}

int			get_cd_flags_2(t_hist_flags *flags, char c)
{
	int		i;
	int		j;

	c == 'c' ? flags->c = 1 : 0;
	c == 'd' ? flags->d = 1 : 0;
	c == 'a' ? flags->a = 1 : 0;
	c == 'n' ? flags->n = 1 : 0;
	c == 'r' ? flags->r = 1 : 0;
	c == 'w' ? flags->w = 1 : 0;
	c == 'p' ? flags->p = 1 : 0;
	c == 's' ? flags->s = 1 : 0;
	if (c != 'c' && c != 'd' && c != 'a' && c != 'n' && c != 'r' && c != 'w'
			&& c != 'p' && c != 's')
		return (set_usage(c, 0));
	i = -1;
	j = 0;
	while (++i < 7)
	{
		if (c == 'a' || c == 'n' || c == 'r' || c == 'w')
			j++;
		if (j > 1)
			return (error_muchflags());
	}
	return (0);
}

int				set_usage(char c, int type)
{
	if (type == 2)
	{
		ft_putendl("shell: history: too many arguments");
		return (1);
	}
	ft_putstr("shell: history: -");
	ft_putchar(c);
	if (type == 0)
		ft_putstr(": invalid option\n");
	else if (type == 1)
		ft_putstr(": option requires an argument\n");
	ft_putstr("history: usage: history [-c] [-d offset] [n] or history");
	ft_putendl(" -awrn [filename] or history -ps arg [arg...]");
	return (1);
}

void			init_cd_flags(t_hist_flags *flags)
{
	flags->c = 0;
	flags->d = 0;
	flags->a = 0;
	flags->n = 0;
	flags->r = 0;
	flags->w = 0;
	flags->p = 0;
	flags->s = 0;
}
