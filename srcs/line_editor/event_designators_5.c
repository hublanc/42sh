/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_designators_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 21:05:10 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/02 21:05:12 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		digit_dollar_designator(t_bang **bang, int a, int digit)
{
	int		j;
	char	**splitted;

	(void)a;
	splitted = ft_cmdsplit((*bang)->to_append);
	if (digit > tablen(splitted))
		return (error_bad_wspec(digit, &splitted));
	while (digit < tablen(splitted) - 1 && splitted[digit])
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

int		digit_star_designator(t_bang **bang, int a)
{
	int		digit;
	int		j;
	char	**splitted;

	(void)a;
	digit = get_first_digit(bang);
	splitted = ft_cmdsplit((*bang)->to_append);
	if (digit > tablen(splitted))
		return (error_bad_wspec(digit, &splitted));
	while (splitted[digit])
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

int		check_backslash(char *command)
{
	int		i;

	i = 0;
	while (command[i] && command[i] != '!')
		i++;
	if (command[i] && command[i] == '!')
	{
		if (i > 0 && command[i - 1] && command[i - 1] == '\\')
			return (0);
	}
	return (1);
}