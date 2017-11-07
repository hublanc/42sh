/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 18:08:42 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 11:18:04 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_history(char **tab, char ***env, t_control **history)
{
	t_hist_flags		flags;
	int					args_pos;
	char				*file;
	int					status;

	status = 0;
	args_pos = 0;
	init_cd_flags(&flags);
	if (!get_cd_flags(&flags, tab, &args_pos) || flags.t > 1)
		return (status);
	file = get_history_file(env);
	if ((!tab[1] || flags.t) && (*history) != NULL
			&& (*history)->length > 0)
		print_history(history);
	if (tab[0] && tab[1]
		&& (flags.a == 1 || flags.n == 1 || flags.w == 1 || flags.r == 1)
		&& tab[args_pos] && args_pos > 1 && file != NULL)
	{
		ft_strdel(&file);
		file = ft_strdup(tab[args_pos]);
	}
	status = ft_history_2(tab, history, file, flags);
	ft_strdel(&file);
	return (status);
}

int			ft_history_2(char **tab, t_control **history, char *file,
			t_hist_flags flags)
{
	if (flags.c == 1)
		(*history) = dll_clear_list(*history);
	if (tab[0] && tab[1] && str_isdigit(tab[1]))
	{
		if (tab[2])
			set_usage('h', 2);
		else
			print_last_elem(history, ft_atoi(tab[1]));
	}
	if (flags.s == 1 && (*history))
	{
		if (tab[2] && !history_s(history, tab, file))
			return (-1);
	}
	if (flags.n == 1 && (*history))
		nflag(history, file);
	if (flags.a == 1 && (*history))
	{
		if (save_history_in_file(history, file) == -1)
			return (-1);
	}
	return (ft_history_3(tab, history, file, flags));
}

int			ft_history_3(char **tab, t_control **history, char *file,
			t_hist_flags flags)
{
	if (flags.w == 1 && (*history))
		if (rewrite_hist_file(history, file) == -1)
			return (-1);
	if (flags.d == 1)
	{
		if (tab[1] && tab[1][2])
			delete_elem_hist(ft_atoi(&tab[1][2]), history, &tab[1][2]);
		else if (tab[2] && (*history))
			delete_elem_hist(ft_atoi(tab[2]), history, tab[2]);
		else if (tab[2] && (!(*history)))
			return (0);
		else
			set_usage('d', 1);
	}
	if (flags.r == 1)
	{
		if (append_hist_file(history, file) == -1)
			return (-1);
	}
	if (flags.p == 1 && tab[2])
		print_pflag(tab);
	return (0);
}

char		*get_history_file(char ***env)
{
	char	*file;

	if (!env || !*env)
		return (NULL);
	file = NULL;
	get_hisfile(*env, &file);
	if (file == NULL)
		return (NULL);
	return (file);
}

void		get_hisfile(char **env, char **file)
{
	t_loc	*loc;
	char	*value;
	int		a;

	value = NULL;
	a = 0;
	if ((!env || !(value = get_elem(&env, "HISTFILE=")))
			&& !(loc = get_loc("HISTFILE")))
		if (get_elem(&env, "HOME="))
		{
			value = ft_strjoin(get_elem(&env, "HOME="), "/");
			value = ft_strapp(value, ".shell_history");
			add_loc("HISTFILE", value);
			ft_strdel(&value);
		}
	if (!(loc = get_loc("HISTFILE")))
		return ;
	value = loc->value;
	if (!value && (!loc || loc->value))
		return ;
	*file = ft_strdup(value);
}
