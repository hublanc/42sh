/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designators_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:07:03 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/31 19:07:04 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_n_first(char *command, int *a, char **result,
			t_control **history)
{
	int		b;
	int		nb;
	t_lst	*tmp;
	char	*str;

	b = 1;
	nb = modified_atoi(&command[1]);
	if ((*history) == NULL || nb > (*history)->length || (*history)->length < 1)
		return (0);
	if (!(str = ft_memalloc(1)))
		return (-1);
	tmp = NULL;
	if (*history && (*history)->end)
		tmp = (*history)->end;
	if (!(get_tmp_lst(&tmp, b, nb, &str)))
	{
		ft_strdel(&str);
		return (0);
	}
	if (get_n_first_2(command, a, &str, result) == 2)
		return (2);
	str = ft_itoa(nb);
	(*a) += ft_strlen(str);
	ft_strdel(&str);
	return (1);
}

int			get_n_first_2(char *command, int *a, char **str, char **result)
{
	int		b;

	if ((b = find_d_dots(command, *a)) && b != 0)
	{
		(*a) += (b - *a);
		if (b + 1 <= (int)ft_strlen(command) && ft_isdigit(command[b + 1]))
			d_dots_found(command, str, b);
		else if (!(ft_isdigit(command[b + 1])))
		{
			ft_strdel(str);
			return (return_error(command, b, 2));
		}
		(*a) += 1;
	}
	append_str(*str, result);
	ft_strdel(str);
	return (1);
}

int			get_n_last(char *command, int *a, char **result,
			t_control **history)
{
	int		b;
	int		nb;
	t_lst	*tmp;
	char	*str;

	b = 1;
	if (command[*a + 2] && !(ft_isdigit(command[*a + 2])))
		return (0);
	nb = modified_atoi(&command[*a + 2]);
	if ((*history) == NULL || nb > (*history)->length || (*history)->length < 1)
		return (0);
	if (!(str = ft_memalloc(1)))
		return (-1);
	tmp = NULL;
	if (*history && (*history)->begin)
		tmp = (*history)->begin;
	if (!(get_tmp_lst(&tmp, b, nb, &str)))
	{
		ft_strdel(&str);
		return (0);
	}
	if (get_n_last_2(command, a, &str, result) == 2)
		return (2);
	return (get_n_last_3(nb, a, &str));
}

int			get_n_last_2(char *command, int *a, char **str, char **result)
{
	int		b;

	if ((b = find_d_dots(command, *a)) && b != 0)
	{
		(*a) += (b - *a - 1);
		if (b + 1 <= (int)ft_strlen(command) && ft_isdigit(command[b + 1]))
		{
			d_dots_found(command, str, b);
			(*a) += 2;
		}
		else if (!(ft_isdigit(command[b + 1])))
		{
			ft_strdel(str);
			return (return_error(command, b, 2));
		}
	}
	append_str(*str, result);
	ft_strdel(str);
	return (1);
}

int			get_n_last_3(int nb, int *a, char **str)
{
	ft_strdel(str);
	*str = ft_itoa(nb);
	(*a) += ft_strlen(*str);
	ft_strdel(str);
	return (1);
}
