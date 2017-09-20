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

	(void)env;
	init_cd_flags(&flags);
	get_cd_flags(&flags, tab);
	if (!tab[1])
		print_history(history);
	else if (flags.s == 1 && (*history))
	{
		if (tab[2])
			save_history(history, tab[2]);
	}
	else if (flags.a == 1 && (*history))
		save_history_in_file(history);
	else if (flags.w == 1 && (*history))		// -w : Need check
		rewrite_hist_file(history);
	else if (flags.d == 1)
	{
		if (tab[2] && str_isdigit(tab[2]) && (*history))
			delete_elem_hist(ft_atoi(tab[2]), history);
		else
			set_usage('d', 1);
	}
	else if (flags.r == 1)
		append_hist_file(history);
	else if (flags.c == 1)
		(*history) = dll_clear_list(*history);
	else if (flags.p == 1 && tab[2])
		print_pflag(tab);
}

void		rewrite_hist_file(t_control **history)
{
	int		fd;
	t_lst	*tmp;

	fd = open(".history", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH);
	tmp = (*history)->end;
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->name, fd);
		tmp = tmp->prev;
	}
	close(fd);
}

void		append_hist_file(t_control **history)
{
	 int	fd;
	 char	*str;

	 fd = open(".history", O_RDWR);
	 while (get_next_line(fd, &str))
	 {
	 	*history = dll_add_new_elem_frnt(*history, str);
	 	ft_strdel(&str);
	 }
	 close (fd);
}

void		print_pflag(char **tab)
{
	int		a;

	a = 2;
	while (tab[a])
	{
		ft_putendl(tab[a]);
		a++;
	}
}

int			str_isdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		delete_elem_hist(int index, t_control **history)
{
	t_lst		*tmp;
	int			a;

	tmp = (*history)->end;
	a = 1;
	while (a < index && tmp != NULL)
	{
		tmp = tmp->prev;
		a++;
	}
	if (tmp && tmp->prev && tmp->next)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	else if (tmp && !tmp->prev && tmp->next)
	{
		(*history)->begin = tmp->next;
		tmp->next->prev = NULL;
	}
	else if (tmp && !tmp->next && tmp->prev)
	{
		(*history)->end = tmp->prev;
		tmp->prev->next = NULL;
	}
	if (tmp && tmp->name)
		free(tmp->name);
	if (tmp)
		free(tmp);
}

void		print_history(t_control **history)
{
	t_lst		*tmp;
	int			u;
	int			i;
	int			sp;

	if (history == NULL)
	{
		ft_putchar('\n');
		return ;
	}
	tmp = (*history)->end;
	u = get_num((*history)->length);
	i = 1;
	while (tmp != NULL)
	{
		ft_putstr("   ");
		sp = get_num(i);
		while (sp < u)
		{
			ft_putchar(' ');
			sp++;
		}
		ft_putnbr(i);
		ft_putstr("  ");
		ft_putendl(tmp->name);
		i++;
		tmp = tmp->prev;
	}
}

int			get_num(int size)
{
	int		num;

	num = 1;
	while (size >= 10)
	{
		size /= 10;
		num++;
	}
	return (num);
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
					set_usage(tab[i][j], 0);
				j++;
			}
		}
		i++;
	}
}

void		set_usage(char c, int type)
{
	ft_putstr("shell: history: -");
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
}
