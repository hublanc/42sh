/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designators_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 23:13:56 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/02 13:34:26 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_elem_arg(t_bang **bang, int a)
{
	int		digit;
	char	**splitted;
	int		i;

	digit = 0;
	((*bang)->index)++;
	if ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& ((*bang)->command[(*bang)->index] == '$'
		|| (*bang)->command[(*bang)->index] == '*'
		|| (*bang)->command[(*bang)->index] == '^'))
		return (word_designator(bang, a));
	else if (which_char_after_digit(bang)
		&& which_char_after_digit(bang) != ' ')
		return (get_elem_arg_3(bang, a));
	else if (!(get_elem_arg_2(bang, a, &digit)))
		return (0);
	splitted = ft_cmdsplit((*bang)->to_append);
	if (digit > tablen(splitted))
		return (error_bad_wspec(digit, &splitted));
	append_in_result(bang, splitted[digit]);
	i = 0;
	del_tabstr(&splitted);
	return (1);
}

int			get_elem_arg_2(t_bang **bang, int a, int *digit)
{
	char		*test;

	test = NULL;
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
	else if ((*bang)->command[(*bang)->index] == '^')
	{
		if (!(chevron_designator(bang, splitted)))
			return (0);
	}
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
