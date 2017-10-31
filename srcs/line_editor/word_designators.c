/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:53:30 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/31 14:41:07 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*wd_designator(char *command, t_control **history)
{
	int		a;
	int		sq;
	char	*result;

	a = 0;
	sq = 0;
	result = NULL;
	if (!(ft_strchr(command, '!')))
		return (ft_strdup(command));
	while (a <= (int)ft_strlen(command) && command[a])
	{
		if (command[a] && (command[a] == '\'' || command[a] == '"'))
			modify_quotes(&sq, command[a], &a);
		else if (command[a] && command[a] == '!' && sq == 0)
		{
			if (!(wd_designator_2(command, &a, &result, history)))
				return (NULL);
		}
		else if (command[a])
			result = ft_str_chr_cat(result, command[a++]);
	}
	add_hist_or_not(history, result);
	isatty(0) ? ft_putendl(result) : 0;
	return (result);
}

int			wd_designator_2(char *command, int *a, char **result,
			t_control **history)
{
	int		returnint;

	returnint = 1;
	if (*a - 1 >= 0 && command[*a - 1] && command[*a - 1] == '\\')
	{
		*result = ft_str_chr_cat(*result, '!');
		(*a)++;
		return (1);
	}
	else if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& command[*a + 1] == '!')
	{
		returnint = get_d_bang(command, a, result, history);
		if (returnint == 0)
		{
			event_not_found(command);
			return (0);
		}
		else if (returnint == 2)
			return (0);
		return (1);
	}
	else
		return (wd_designator_3(command, a, result, history));
}

int			wd_designator_3(char *command, int *a, char **result,
			t_control **history)
{
	int		returnint;

	returnint = 1;
	if (*a + 2 <= (int)ft_strlen(command) && command[*a + 1]
			&& command[*a + 1] == ' ' && ft_isalnum(command[*a + 2]))
	{
		(*a) += 2;
		return (1);
	}
	else if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& ft_isdigit(command[*a + 1]))
	{
		returnint = get_n_first(command, a, result, history);
		if (returnint == 0)
		{
			event_not_found(command);
			return (0);
		}
		else if (returnint == 2)
			return (0);
		return (1);
	}
	else
		return (wd_designator_4(command, a, result, history));
}

int			wd_designator_4(char *command, int *a, char **result,
			t_control **history)
{
	int		returnint;

	returnint = 1;
	if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& command[*a + 1] == '-')
	{
		returnint = get_n_last(command, a, result, history);
		if (returnint == 0)
		{
			event_not_found(command);
			return (0);
		}
		else if (returnint == 2)
			return (0);
		return (1);
	}
	else
		return (wd_designator_5(command, a, result, history));
}

int			wd_designator_5(char *command, int *a, char **result,
			t_control **history)
{
	int		returnint;

	returnint = 1;
	if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& ft_isalnum(command[*a + 1]) && command[*a + 1] != '!')
	{
		returnint = get_c_first(command, a, result, history);
		if (returnint == 0)
		{
			event_not_found(command);
			return (0);
		}
		else if (returnint == 2)
			return (0);
		return (1);
	}
	else if (*a + 1 >= (int)ft_strlen(command))
	{
		set_error(1, command);
		return (0);
	}
	else
		return (wd_designator_6(command));
}

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

// Need to protec return ; if return == -1, bullshit with malloc, return NULL
// Need to protec return of cmdsplit too
// When returning an error, free everything

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
	char	*test;
	char	*str;

	if (!(str = ft_memalloc(1)))
		return (-1);
	b = 1;
	if (command[*a + 2] && !(ft_isdigit(command[*a + 2])))
		return (0);
	nb = modified_atoi(&command[*a + 2]);
	if (nb > (*history)->length || (*history)->length < 1)
		return (0);
	tmp = NULL;
	if (*history && (*history)->begin)
		tmp = (*history)->begin;
	else
		return (0);
	while (tmp != NULL && b < nb)
	{
		tmp = tmp->next;
		b++;
	}
	if (tmp)
	{
		b = 0;
		while (tmp->name[b])
		{
			str = ft_str_chr_cat(str, tmp->name[b]);
			b++;
		}
	}
	if (find_d_dots(command, *a))
	{
		b = find_d_dots(command, *a);
		(*a) += (b - *a - 1);
		if (b + 1 <= (int)ft_strlen(command) && ft_isdigit(command[b + 1]))
		{
			d_dots_found(command, &str, b);
			(*a) += 2;
		}
		else if (!(ft_isdigit(command[b + 1])))
			return (return_error(command, b, 2));
	}
	b = 0;
	while (str[b])
	{
		*result = ft_str_chr_cat(*result, str[b]);
		b++;
	}
	ft_strdel(&str);
	test = ft_itoa(nb);
	(*a) += ft_strlen(test);
	free(test);
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
	while (command[*a + b] && command[*a + b] != '!' && command[*a + b] != ' '
			&& command[*a + b] != ':')
	{
		test = ft_str_chr_cat(test, command[*a + b]);
		b++;
	}
	if (!(*history) || !((*history)->begin))
	{
		ft_strdel(&test);
		return (0);
	}
	tmp = (*history)->begin;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->name, test, ft_strlen(test)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		b = 0;
		while (tmp->name[b])
		{
			str = ft_str_chr_cat(str, tmp->name[b]);
			b++;
		}
	}
	else
	{
		ft_strdel(&test);
		ft_strdel(&str);
		return (0);
	}
	if (find_d_dots(command, *a))
	{
		b = find_d_dots(command, *a);
		(*a) += (b - *a);
		if (b + 1 <= (int)ft_strlen(command) && ft_isdigit(command[b + 1]))
			d_dots_found(command, &str, b);
		else if (!(ft_isdigit(command[b + 1])))
			return (return_error(command, b, 2));
	}
	b = 0;
	while (str[b])
	{
		*result = ft_str_chr_cat(*result, str[b]);
		b++;
	}
	ft_strdel(&str);
	(*a) += ft_strlen(test) + 1;
	ft_strdel(&test);
	return (1);
}

// NEED CHECK
void		modify_quotes(int *sq, char c, int *a)
{
	if (c == '\'')
	{
		if (*sq >= 1)
			(*sq)--;
		else if (*sq == 0)
			(*sq)++;
	}
	(*a)++;
}
