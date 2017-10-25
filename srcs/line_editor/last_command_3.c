/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:28:49 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/25 17:21:01 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_n_2(char *tmp_str, char **str)
{
	int		a;

	a = 0;
	while (tmp_str[a])
	{
		(*str) = ft_str_chr_cat(*str, tmp_str[a]);
		a++;
	}
}

int			get_n_last(char *command, char **str, t_control **history,
			int *index)
{
	int		a;
	int		b;
	t_lst	*tmp;

	a = 1;
	if (command[2] && !ft_isdigit(command[2]))
		return (0);
	b = ft_atoi(&command[2]);
	if (b > (*history)->length || b == 0)
		return (0);
	tmp = NULL;
	if (*history && (*history)->begin)
		tmp = (*history)->begin;
	while (tmp != NULL && a < b)
	{
		tmp = tmp->next;
		a++;
	}
	if (tmp)
		get_n_2(tmp->name, str);
	a = 0;
	while (command[a] && command[a] != ' ')
		a++;
	(*index) += a;
	return (1);
}

int			get_n_first(char *command, char **str, t_control **history,
			int *index)
{
	int		a;
	int		b;
	t_lst	*tmp;

	a = 1;
	b = ft_atoi(&command[1]);
	if (b > (*history)->length || b == 0)
		return (0);
	tmp = NULL;
	if (*history && (*history)->end)
		tmp = (*history)->end;
	while (tmp != NULL && a < b)
	{
		tmp = tmp->prev;
		a++;
	}
	if (tmp)
		get_n_2(tmp->name, str);
	a = 0;
	while (command && command[a] && command[a] != ' ')
		a++;
	(*index) += a;
	return (1);
}

void		get_line_again(char *command, int *index, char **str,
			t_control **history)
{
	int		a;

	a = 0;
	while (a != *index - 1)
	{
		(*str) = ft_str_chr_cat(*str, command[a]);
		a++;
	}
	(void)history;
	a = 0;
	while (command[a] && command[a] != ' ')
		a++;
	(*index) += a;
}

void		get_last_command_3(char *str, int *index, char **tmp)
{
	int		a;

	a = 0;
	while (str && str[a] && str[a] != ' ')
		a++;
	(*index) += a;
	ft_strdel(tmp);
}
