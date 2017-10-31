/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designators_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:07:45 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/31 19:07:46 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_tmp_cfirst(t_lst **tmp, char *test, char **str)
{
	while ((*tmp) != NULL)
	{
		if (ft_strncmp((*tmp)->name, test, ft_strlen(test)) == 0)
			break ;
		(*tmp) = (*tmp)->next;
	}
	if (tmp)
		append_str((*tmp)->name, str);
	else
	{
		ft_strdel(&test);
		ft_strdel(str);
		return (0);
	}
	return (1);
}

int			get_c_first(char *command, int *a, char **result,
			t_control **history)
{
	int		b;
	char	*test;
	t_lst	*tmp;
	char	*str;

	if (!(str = ft_memalloc(1)))
		return (-1);
	if (!(test = ft_memalloc(1)))
		return (-1);
	tmp = NULL;
	b = 1;
	get_c_first_3(&test, command, a, b);
	if (!(get_c_first_check_history(history, &str, &test)))
		return (0);
	tmp = (*history)->begin;
	if (!(get_tmp_cfirst(&tmp, test, &str)))
		return (0);
	if (get_c_first_2(command, a, &str, result) == 2)
		return (2);
	(*a) += ft_strlen(test) + 1;
	ft_strdel(&test);
	return (1);
}

int			get_c_first_2(char *command, int *a, char **str, char **result)
{
	int		b;

	if ((b = find_d_dots(command, *a)) && b != 0)
	{
		(*a) += (b - *a);
		if (b + 1 <= (int)ft_strlen(command) && ft_isdigit(command[b + 1]))
			d_dots_found(command, str, b);
		else if (!(ft_isdigit(command[b + 1])))
			return (return_error(command, b, 2));
	}
	b = 0;
	append_str(*str, result);
	ft_strdel(str);
	return (1);
}

void		get_c_first_3(char **test, char *command, int *a, int b)
{
	while (command[*a + b] && command[*a + b] != '!' && command[*a + b] != ' '
		&& command[*a + b] != ':')
	{
		(*test) = ft_str_chr_cat(*test, command[*a + b]);
		b++;
	}
}

int			get_c_first_check_history(t_control **history, char **str,
			char **test)
{
	if (!(*history) || !((*history)->begin))
	{
		ft_strdel(str);
		ft_strdel(test);
		return (0);
	}
	return (1);
}
