/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:08:42 by mameyer           #+#    #+#             */
/*   Updated: 2017/09/18 18:08:44 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_history(char **tab, char ***env, t_hist **history)
{
	t_hist_flags		flags;

	(void)env;
	init_cd_flags(&flags);
	get_cd_flags(&flags, tab);
	if (!tab[1])
		print_history(history);
}

void		print_history(t_hist **history)
{
	t_control	*rev_hist;
	t_hist		*tmp;
	t_lst		*tmp2;

	rev_hist = NULL;
	tmp = *history;
	while (tmp != NULL)
	{
		rev_hist = dll_add_new_elem_frnt(rev_hist, tmp->cmd);
		tmp = tmp->next;
	}
	tmp2 = rev_hist->begin;

	rev_hist = dll_clear_list(rev_hist);
}

void		get_cd_flags(t_hist_flags *flags, char **tab)
{
	int		i;
	int		j;

	i = 1;
	while (tab[i] && tab[i][0] == '-')
	{
		j = 0;
		if (tab[i][j] && tab[i][j] == '-')
		{
			j++;
			while (tab[i] && tab[i][j])
			{
				if (tab[i][j] && tab[i][j] == 'c')
					flags->c = 1;
				else if (tab[i][j] && tab[i][j] == 'd')
					flags->d = 1;
				else if (tab[i][j] && tab[i][j] == 'a')
					flags->a = 1;
				else if (tab[i][j] && tab[i][j] == 'n')
					flags->n = 1;
				else if (tab[i][j] && tab[i][j] == 'r')
					flags->r = 1;
				else if (tab[i][j] && tab[i][j] == 'w')
					flags->w = 1;
				else if (tab[i][j] && tab[i][j] == 'p')
					flags->p = 1;
				else if (tab[i][j] && tab[i][j] == 's')
					flags->s = 1;
				else if (tab[i][j])
					set_usage(tab[i][j]);
				j++;
			}
		}
		i++;
	}
}

void		set_usage(char c)
{
	ft_putstr("shell: history: -");
	ft_putchar(c);
	ft_putstr(" invalid option\n");
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
}
