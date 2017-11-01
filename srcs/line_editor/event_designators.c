/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:29:01 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/01 13:29:03 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*bang_events(char *command, t_control **history)
{
	t_bang	*bang;
	char	*result;

	if (!(ft_strchr(command, '!')))
		return (ft_strdup(command));
	if (!(malloc_struct_bang(&bang, command)))
		return (NULL);
	if (!(bang_events_2(&bang, history)))
	{
		free_struct_bang(&bang);
		return (NULL);
	}
	add_hist_or_not(history, bang->result);
	result = ft_strdup(bang->result);
	ft_putendl(result);
	free_struct_bang(&bang);
	return (result);
}

int			bang_events_2(t_bang **bang, t_control **history)
{
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index])
	{
		if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
			&& (*bang)->command[(*bang)->index] == '\'')
			is_quote(bang);
		else if ((*bang)->index < (*bang)->len
			&& (*bang)->command[(*bang)->index]
			&& (*bang)->quotes == 0 && ((*bang)->command[(*bang)->index] == '!'
				|| (*bang)->command[(*bang)->index] == ':'))
		{
			if (!(bang_events_3(bang, history)))
				return (0);
			if ((*bang)->result == NULL || ft_strlen((*bang)->result) < 1)
				(*bang)->result = ft_strdup((*bang)->to_append);
		}
		else if ((*bang)->index < (*bang)->len
			&& (*bang)->command[(*bang)->index])
		{
			(*bang)->result = ft_str_chr_cat((*bang)->result,
				(*bang)->command[(*bang)->index]);
			((*bang)->index)++;
		}
	}
	return (1);
}

int			bang_events_3(t_bang **bang, t_control **history)
{
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' ')
	{
		if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
			&& (*bang)->command[(*bang)->index] == '!')
		{
			ft_strdel(&(*bang)->to_append);
			(*bang)->to_append = ft_memalloc(1);
			if (!(get_elem_hist(bang, history)))
				return (0);
		}
		else if ((*bang)->index < (*bang)->len
			&& (*bang)->command[(*bang)->index]
			&& (*bang)->command[(*bang)->index] == ':')
		{
			if (!(get_elem_arg(bang, (*bang)->index)))
				return (0);
		}
		else
			((*bang)->index)++;
	}
	return (1);
}

int			hist_event_not_found(t_bang **bang, int a)
{
	ft_putstr("shell: ");
	while ((*bang)->command[a])
		ft_putchar((*bang)->command[a++]);
	ft_putendl(": event_not_found");
	return (0);
}

int			get_elem_hist(t_bang **bang, t_control **history)
{
	int		a;

	a = (*bang)->index;
	((*bang)->index)++;
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' '
		&& (*bang)->command[(*bang)->index] != ':')
	{
		if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
			&& (*bang)->command[(*bang)->index] == '!')
		{
			if (!(get_double_bang(bang, history, a)))
				return (0);
		}
		else if (!(get_elem_hist_2(bang, history, a)))
			return (0);
	}
	return (1);
}

int			get_elem_hist_2(t_bang **bang, t_control **history, int a)
{
	if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& ft_isdigit((*bang)->command[(*bang)->index]))
	{
		if (!(get_n_first(bang, history, a)))
			return (0);
	}
	else if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] == '-')
	{
		if (!(get_n_last(bang, history, a)))
			return (0);
	}
	else if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& ft_isalpha((*bang)->command[(*bang)->index]))
	{
		if (!(get_c_last(bang, history, a)))
			return (0);
	}
	return (1);
}

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

int			return_cond(t_bang **bang, int a, t_lst *tmp)
{
	if (tmp)
		(*bang)->to_append = ft_strdup(tmp->name);
	else
		return (hist_event_not_found(bang, a));
	return (1);
}

int			get_elem_arg(t_bang **bang, int a)
{
	int		digit;
	char	**splitted;
	int		i;

	digit = 0;
	((*bang)->index)++;
	if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& ((*bang)->command[(*bang)->index] == '$'
		|| (*bang)->command[(*bang)->index] == '*'))
		return (word_designator(bang, a));
	else if (!(get_elem_arg_2(bang, a, &digit)))
		return (0);
	splitted = ft_cmdsplit((*bang)->to_append);
	if (digit > tablen(splitted))
		return (error_bad_wspec(digit, &splitted));
	append_in_result(bang, splitted[digit]);
	i = 0;
	while (splitted[i])
	{
		ft_strdel(&splitted[i]);
		i++;
	}
	free(splitted[i]);
	return (1);
}

void		append_in_result(t_bang **bang, char *to_append)
{
	int		i;

	i = 0;
	while (to_append[i])
	{
		(*bang)->result = ft_str_chr_cat((*bang)->result, to_append[i]);
		i++;
	}
}

int			get_elem_arg_2(t_bang **bang, int a, int *digit)
{
	char		*test;

	test = ft_memalloc(1);
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index] != ' ')
	{
		if ((*bang)->command[(*bang)->index]
			&& ((*bang)->command[(*bang)->index] == ':'
			|| !(ft_isdigit((*bang)->command[(*bang)->index]))))
			return (error_unrecognized_hmod(bang, &test, a));
		if ((*bang)->command[(*bang)->index]
			&& ft_isdigit((*bang)->command[(*bang)->index]))
			test = ft_str_chr_cat(test, (*bang)->command[(*bang)->index]);
		((*bang)->index)++;
	}
	atoi_free(digit, &test);
	return (1);
}

void		atoi_free(int *digit, char **test)
{
	(*digit) = ft_atoi(*test);
	ft_strdel(test);
}

int			word_designator(t_bang **bang, int a)
{
	char	**splitted;
	int		digit;
	int		i;

	i = 0;
	digit = 0;
	splitted = ft_cmdsplit((*bang)->to_append);
	while (splitted[digit])
		digit++;
	if ((*bang)->command[(*bang)->index] == '$')
		dollar_designator(bang, splitted, digit);
	else if ((*bang)->command[(*bang)->index] == '*')
		star_designator(bang, splitted);
	digit = 0;
	while (splitted[digit])
	{
		ft_strdel(&(splitted[digit]));
		digit++;
	}
	(void)a;
	free(splitted);
	return (1);
}

void		dollar_designator(t_bang **bang, char **splitted, int digit)
{
	int		i;

	i = 0;
	while (splitted[digit - 1] && splitted[digit - 1][i])
	{
		(*bang)->result = ft_str_chr_cat((*bang)->result,
			splitted[digit - 1][i]);
		i++;
	}
}

void		star_designator(t_bang **bang, char **splitted)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (splitted[j])
	{
		i = 0;
		while (splitted[j] && splitted[j][i])
		{
			(*bang)->result = ft_str_chr_cat((*bang)->result, splitted[j][i]);
			i++;
		}
		(*bang)->result = ft_str_chr_cat((*bang)->result, ' ');
		j++;
	}
}

void		is_quote(t_bang **bang)
{
	if ((*bang)->quotes == 0)
		(*bang)->quotes = 1;
	else if ((*bang)->quotes == 1)
		(*bang)->quotes = 0;
	((*bang)->index)++;
}

int			error_unrecognized_hmod(t_bang **bang, char **test, int a)
{
	ft_putstr("shell: ");
	ft_putstr(&(*bang)->command[a]);
	ft_putendl(": unrecognized history modifier");
	ft_strdel(test);
	return (0);
}

int			error_bad_wspec(int digit, char ***splitted)
{
	ft_putstr("shell: :");
	ft_putnbr(digit);
	ft_putendl(": bad word specifier");
	digit = 0;
	while ((*splitted)[digit])
	{
		ft_strdel(&(*splitted)[digit]);
		digit++;
	}
	free(*splitted);
	return (0);
}

int			malloc_struct_bang(t_bang **bang, char *command)
{
	if (!((*bang) = ft_memalloc(sizeof(t_bang))))
		return (0);
	if (!((*bang)->result = ft_memalloc(1)))
		return (0);
	if (!((*bang)->to_append = ft_memalloc(1)))
		return (0);
	if (((*bang)->command = ft_strdup(command)) == NULL)
		return (0);
	(*bang)->index = 0;
	(*bang)->len = ft_strlen(command);
	(*bang)->quotes = 0;
	return (1);
}

void		free_struct_bang(t_bang **bang)
{
	ft_strdel(&(*bang)->result);
	ft_strdel(&(*bang)->to_append);
	ft_strdel(&(*bang)->command);
	free(*bang);
	bang = NULL;
}
