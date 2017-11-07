/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:21:36 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/21 22:21:40 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		delete_elem_hist(int index, t_control **history, char *error)
{
	t_lst		*tmp;
	int			a;

	if (index > (*history)->length || index <= 0)
	{
		ft_putstr("shell: history: ");
		ft_putstr(error);
		ft_putendl(": history position out of range");
		return ;
	}
	tmp = (*history)->end;
	a = 1;
	while (a < index && tmp != NULL)
	{
		tmp = tmp->prev;
		a++;
	}
	delete_elem_hist_2(tmp, history);
	delete_elem(&tmp);
	((*history)->length)--;
	if ((*history)->length < 1)
	{
		free(*history);
		(*history) = NULL;
	}
}

void		delete_elem_hist_2(t_lst *tmp, t_control **history)
{
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
}

void		print_last_elem(t_control **history, int last)
{
	int		a;
	t_lst	*tmp;
	int		u;
	int		sp;

	if (last > (*history)->length)
		last = (*history)->length + 1;
	tmp = (*history)->end;
	u = get_num((*history)->length);
	a = -1;
	while (tmp != NULL && ++a < (*history)->length - last)
		tmp = tmp->prev;
	while (tmp != NULL)
	{
		ft_putstr("   ");
		sp = get_num(a) - 1;
		while (++sp < u)
			ft_putchar(' ');
		ft_putnbr(a);
		ft_putstr("  ");
		ft_putendl(tmp->name);
		a++;
		tmp = tmp->prev;
	}
}

void		print_history(t_control **history)
{
	t_lst		*tmp;
	int			u;
	int			i;
	int			sp;

	tmp = (*history)->end;
	u = get_num((*history)->length);
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->name && ft_strlen(tmp->name) > 0)
		{
			ft_putstr("   ");
			sp = get_num(i) - 1;
			while (++sp < u)
				ft_putchar(' ');
			ft_putnbr(i);
			ft_putstr("  ");
			ft_putendl(tmp->name);
			i++;
		}
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
