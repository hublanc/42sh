/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:22:29 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/07 16:13:32 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_cd_flags(t_hist_flags *flags, char **tab, int *args_pos)
{
	int		i;
	int		j;

	i = 1;
	while (tab[i] && tab[i][0] == '-')
	{
		j = 0;
		if (tab[i][j] && tab[i][j] == '-' && tab[i][j + 1]
			&& tab[i][j + 1] == 'd')
		{
			flags->d = 1;
			i++;
		}
		else if (tab[i][j] && tab[i][j] == '-' && tab[i][j + 1]
			&& tab[i][j + 1] != '-')
		{
			j++;
			while (tab[i] && tab[i][j])
			{
				if (!(get_cd_flags_2(flags, tab[i][j++])))
					return (0);
			}
		}
		// Check error
		else if ((tab[i][j] && tab[i][j] == '-' && !(tab[i][j + 1]))
			|| (tab[i][j] && tab[i][j] == '-' && tab[i][j + 1] && tab[i][j + 1] == '-'))
			ft_putendl("shell: history: -: numeric argument required");
		i++;
	}
	if (flags->more > 1)
	{
		ft_putendl("shell: history: cannot use more than one of -anrw");
		return (0);
	}
	if (flags->c == 1)
		flags->d = 0;
	*args_pos = i;
	return (1);
}

int			get_cd_flags_2(t_hist_flags *flags, char c)
{
	if (c == 'c')
		flags->c = 1;
	else if (c == 'd')
		flags->d = 1;
	else if (c == 'a')
	{
		(flags->more)++;
		flags->a = 1;
	}
	else if (c == 'n')
	{
		(flags->more)++;
		flags->n = 1;
	}
	else if (c == 'r')
	{
		(flags->more)++;
		flags->r = 1;
	}
	else if (c == 'w')
	{
		(flags->more)++;
		flags->w = 1;
	}
	else if (c == 'p')
		flags->p = 1;
	else if (c == 's')
		flags->s = 1;
	else
	{
		set_usage(c, 0);
		return (0);
	}
	return (1);
}

void		set_usage(char c, int type)
{
	if (type == 2)
	{
		ft_putendl("42sh: history: too many arguments");
		return ;
	}
	ft_putstr("42sh: history: -");
	ft_putchar(c);
	if (type == 0)
		ft_putstr(": invalid option\n");
	else if (type == 1)
		ft_putstr(": option requires an argument\n");
	ft_putstr("history: usage: history [-c] [-d offset] [n] or history");
	ft_putendl(" -awrn [filename] or history -ps arg [arg...]");
}

void		init_cd_flags(t_hist_flags *flags)
{
	flags->c = 0;
	flags->d = 0;
	flags->a = 0;
	flags->n = 0;
	flags->r = 0;
	flags->w = 0;
	flags->p = 0;
	flags->s = 0;
	flags->more = 0;
}
