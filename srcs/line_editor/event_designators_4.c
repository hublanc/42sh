/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designators_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:32:01 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/02 19:32:03 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		chevron_designator(t_bang **bang, char **splitted)
{
	int		i;

	if (splitted && !(splitted[1]))
		return (0);
	i = 0;
	while (splitted[1] && splitted[1][i])
	{
		(*bang)->result = ft_str_chr_cat((*bang)->result,
			splitted[1][i]);
		i++;
	}
	return (1);
}

int		get_elem_arg_3(t_bang **bang, int a)
{
	if (which_char_after_digit(bang) == '-')
		return (hyphen_designator(bang, a));
	else if (which_char_after_digit(bang) == '*')
		return (digit_star_designator(bang, a));
	return (0);
}

int		hyphen_designator(t_bang **bang, int a)
{
	int		first_digit;

	(void)a;
	first_digit = get_first_digit(bang);
	if ((*bang)->index + 1 < (*bang)->len && (*bang)->command[(*bang)->index]
		&& (*bang)->command[(*bang)->index + 1]
		&& ft_isdigit((*bang)->command[(*bang)->index + 1]))
		return (digit_hyphen_digit_designator(bang, first_digit));
	else
		return (digit_dollar_designator(bang, a, first_digit));
	return (1);
}

int		digit_hyphen_digit_designator(t_bang **bang, int digit)
{
	int		second_digit;
	char	**splitted;
	int		j;

	((*bang)->index)++;
	second_digit = get_first_digit(bang);
	splitted = ft_cmdsplit((*bang)->to_append);
	if (digit > tablen(splitted))
		return (error_bad_wspec(digit, &splitted));
	else if (second_digit > tablen(splitted))
		return (error_bad_wspec(second_digit, &splitted));
	while (digit < tablen(splitted) && splitted[digit] && digit <= second_digit)
	{
		j = 0;
		while (splitted[digit][j])
		{
			(*bang)->result = ft_str_chr_cat((*bang)->result,
				splitted[digit][j]);
			j++;
		}
		(*bang)->result = ft_str_chr_cat((*bang)->result, ' ');
		digit++;
	}
	del_tabstr(&splitted);
	return (1);
}

int		get_first_digit(t_bang **bang)
{
	char	*test;
	int		digit;

	test = NULL;
	while ((*bang)->index < (*bang)->len && (*bang)->command[(*bang)->index]
		&& ft_isdigit((*bang)->command[(*bang)->index]))
	{
		test = ft_str_chr_cat(test, (*bang)->command[(*bang)->index]);
		((*bang)->index)++;
	}
	digit = ft_atoi(test);
	ft_strdel(&test);
	return (digit);
}
