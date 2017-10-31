/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designators_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:06:05 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/31 19:06:06 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			wd_designator_6(char *command)
{
	event_not_found(command);
	return (0);
}

int			get_d_bang(char *command, int *a, char **result,
			t_control **history)
{
	int		b;
	char	*str;

	if (!(str = ft_memalloc(1)))
		return (0);
	b = 0;
	if (!(*history) || (*history)->length <= 0
			|| (!((*history)->begin) && (*history)->begin->name))
		return (0);
	append_str((*history)->begin->name, &str);
	if (find_d_dots(command, *a))
	{
		b = find_d_dots(command, *a);
		if (b + 1 <= (int)ft_strlen(command) && ft_isdigit(command[b + 1]))
			d_dots_found(command, &str, b);
		else if (!(ft_isdigit(command[b + 1])))
			return (return_error(command, b, 2));
		else
			return (return_error(command, b, 1));
		(*a) += 2;
	}
	append_str(str, result);
	ft_strdel(&str);
	(*a) += 2;
	return (1);
}

void		append_str(char *to_cpy, char **str)
{
	int		a;

	a = 0;
	while (to_cpy[a])
	{
		*str = ft_str_chr_cat(*str, to_cpy[a]);
		a++;
	}
}

void		d_dots_found(char *command, char **str, int b)
{
	char	**splitted;
	int		digit;

	splitted = ft_cmdsplit(*str);
	digit = ft_atoi(&command[b + 1]);
	if (digit <= tablen(splitted) && splitted[digit])
	{
		ft_strdel(str);
		b = 0;
		while (splitted[digit][b])
		{
			*str = ft_str_chr_cat(*str, splitted[digit][b]);
			b++;
		}
		b = 0;
		while (splitted[b])
		{
			ft_strdel(&splitted[b]);
			b++;
		}
		free(splitted);
	}
}

int			get_tmp_lst(t_lst **tmp, int b, int nb, char **str)
{
	while ((*tmp) != NULL && b < nb)
	{
		(*tmp) = (*tmp)->prev;
		b++;
	}
	if (tmp)
		append_str((*tmp)->name, str);
	else
		return (0);
	return (1);
}
