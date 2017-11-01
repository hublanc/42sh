/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designators_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 23:13:01 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/01 23:13:03 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_double_bang(t_bang **bang, t_control **history, int a)
{
	(void)a;
	if ((*history) == NULL || ((*history) && (*history)->length < 1))
		return (hist_event_not_found(bang, a));
	if ((*history) && (*history)->begin && (*history)->begin->name)
		(*bang)->to_append = ft_strdup((*history)->begin->name);
	if ((*bang)->to_append == NULL)
		return (0);
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' '
		&& (*bang)->command[(*bang)->index] != ':')
		((*bang)->index)++;
	return (1);
}

int			get_n_first(t_bang **bang, t_control **history, int a)
{
	int		digit;
	char	*test;
	t_lst	*tmp;

	test = ft_memalloc(1);
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' '
		&& (*bang)->command[(*bang)->index] != ':')
	{
		test = ft_str_chr_cat(test, (*bang)->command[(*bang)->index]);
		((*bang)->index)++;
	}
	atoi_free(&digit, &test);
	if ((*history) == NULL || ((*history) && (*history)->length < digit))
		return (hist_event_not_found(bang, a));
	tmp = (*history)->end;
	while (tmp != NULL && digit > 1)
	{
		tmp = tmp->prev;
		digit--;
	}
	return (return_cond(bang, a, tmp));
}

int			get_n_last(t_bang **bang, t_control **history, int a)
{
	int		digit;
	char	*test;
	t_lst	*tmp;

	((*bang)->index)++;
	test = ft_memalloc(1);
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' '
		&& (*bang)->command[(*bang)->index] != ':')
	{
		test = ft_str_chr_cat(test, (*bang)->command[(*bang)->index]);
		((*bang)->index)++;
	}
	atoi_free(&digit, &test);
	if ((*history) == NULL || ((*history) && (*history)->length < digit))
		return (hist_event_not_found(bang, a));
	tmp = (*history)->begin;
	while (tmp != NULL && digit > 1)
	{
		tmp = tmp->next;
		digit--;
	}
	return (return_cond(bang, a, tmp));
}

int			get_c_last(t_bang **bang, t_control **history, int a)
{
	char	*test;
	t_lst	*tmp;

	test = ft_memalloc(1);
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' '
		&& (*bang)->command[(*bang)->index] != ':')
	{
		test = ft_str_chr_cat(test, (*bang)->command[(*bang)->index]);
		((*bang)->index)++;
	}
	if ((*history) == NULL || ((*history) && (*history)->length < 1))
		return (hist_event_not_found(bang, a));
	tmp = (*history)->begin;
	while (tmp != NULL)
	{
		if (ft_strncmp(test, tmp->name, ft_strlen(test)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (return_cond(bang, a, tmp));
}
