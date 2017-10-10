/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:28:49 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/03 14:28:50 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_n_last(char *command, char **str, t_control **history,
			int *index)
{
	int		a;
	int		b;
	t_lst	*tmp;

	a = 1;
	b = ft_atoi(&command[2]);
	tmp = NULL;
	if (*history && (*history)->begin)
		tmp = (*history)->begin;
	while (tmp != NULL && a < b)
	{
		tmp = tmp->next;
		a++;
	}
	if (tmp)
	{
		a = 0;
		while (tmp->name[a])
		{
			(*str) = ft_str_chr_cat(*str, tmp->name[a]);
			a++;
		}
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;
}

void		get_n_first(char *command, char **str, t_control **history,
			int *index)
{
	int		a;
	int		b;
	t_lst	*tmp;

	a = 1;
	b = ft_atoi(&command[1]);
	tmp = NULL;
	if (*history && (*history)->end)
		tmp = (*history)->end;
	while (tmp != NULL && a < b)
	{
		tmp = tmp->prev;
		a++;
	}
	if (tmp)
	{
		a = 0;
		while (tmp->name[a])
		{
			(*str) = ft_str_chr_cat(*str, tmp->name[a]);
			a++;
		}
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;
}

void		get_line_again(char *command, int *index, char **str,
			t_control **history)
{
	int		a;

	a = 0;
	while (a != *index)
	{
		(*str) = ft_str_chr_cat(*str, command[a]);
		a++;
	}
	(void)history;
	while (command[*index] && command[*index] != ' ')
		(*index)++;
}
