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

void		ft_history(char **tab, char ***env, t_control **history)
{
	t_hist_flags		flags;
	int					args_pos;
	char				*file;

	(void)env;
	args_pos = 0;
	init_cd_flags(&flags);
	get_cd_flags(&flags, tab, &args_pos);
	file = ft_strdup(".history");
	if (!tab[1] && (*history) != NULL && (*history)->length > 0)
		print_history(history);
	if (tab[0] && tab[1]
		&& (flags.a == 1 || flags.n == 1 || flags.w == 1 || flags.r == 1)
		&& tab[args_pos] && args_pos > 1)
	{
		ft_strdel(&file);
		file = ft_strdup(tab[args_pos]);
	}
	ft_history_2(tab, history, file, flags);
	free(file);
	file = NULL;
}

void		ft_history_2(char **tab, t_control **history, char *file,
			t_hist_flags flags)
{
	if (flags.c == 1)
	{
		(*history) = dll_clear_list(*history);
		(*history) = NULL;
	}
	if (tab[0] && tab[1] && str_isdigit(tab[1]))
	{
		if (tab[2])
			set_usage('h', 2);
		else
			print_last_elem(history, ft_atoi(tab[1]));
	}
	if (flags.s == 1 && (*history))
	{
		if (tab[2])
			save_history(history, tab[2]);
	}
	if (flags.n == 1 && (*history))
		nflag(history, file);
	if (flags.a == 1 && (*history))
		save_history_in_file(history, file);
	ft_history_3(tab, history, file, flags);
}

void		ft_history_3(char **tab, t_control **history, char *file,
			t_hist_flags flags)
{
	if (flags.w == 1 && (*history))
		rewrite_hist_file(history, file);
	if (flags.d == 1)
	{
		if (tab[2] && str_isdigit(tab[2]) && (*history))
			delete_elem_hist(ft_atoi(tab[2]), history);
		else
			set_usage('d', 1);
	}
	if (flags.r == 1)
		append_hist_file(history, file);
	if (flags.p == 1 && tab[2])
		print_pflag(tab);
}
