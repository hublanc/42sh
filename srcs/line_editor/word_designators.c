/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:53:30 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/30 16:26:12 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*wd_designator(char *command, t_control **history)
{
	int		a;
	int		sq;
	int		dq;
	char	*result;

	a = 0;
	sq = 0;
	dq = 0;
	result = NULL;
	if (!(ft_strchr(command, '!')))
		return (ft_strdup(command));
	while (a <= (int)ft_strlen(command) && command[a])
	{
		if (command[a] && (command[a] == '\'' || command[a] == '"'))
			modify_quotes(&sq, &dq, command[a], &a);
		else if (command[a] && command[a] == '!' && sq == 0 && dq == 0)
		{
			if (!(wd_designator_2(command, &a, &result, history)))
				return (NULL);
		}
		else if (command[a])
		{
			result = ft_str_chr_cat(result, command[a]);
			a++;
		}
	}
	add_hist_or_not(history, result);
	isatty(0) ? ft_putendl(result) : 0;
	return (result);
}

int			wd_designator_2(char *command, int *a, char **result,
			t_control **history)
{
	if (*a - 1 >= 0 && command[*a - 1] && command[*a - 1] == '\\')
	{
		*result = ft_str_chr_cat(*result, '!');
		(*a)++;
	}
	else if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& command[*a + 1] == '!')
	{
		if (!(get_d_bang(command, a, result, history)))
		{
			event_not_found(command);
			return (0);
		}
		return (1);
	}
	else if (*a + 2 <= (int)ft_strlen(command) && command[*a + 1]
			&& command[*a + 1] == ' ' && ft_isalnum(command[*a + 2]))
	{
		(*a) += 2;
	}
	else if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& ft_isdigit(command[*a + 1]))
	{
		if (!(get_n_first(command, a, result, history)))
		{
			event_not_found(command);
			return (0);
		}
	}
	else if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& command[*a + 1] == '-')
	{
		if (!(get_n_last(command, a, result, history)))
		{
			event_not_found(command);
			return (0);
		}
	}
	else if (*a + 1 <= (int)ft_strlen(command) && command[*a + 1]
			&& ft_isalnum(command[*a + 1]) && command[*a + 1] != '!')
	{
		if (!(get_c_first(command, a, result, history)))
		{
			event_not_found(command);
			return (0);
		}
		return (1);
	}
	else
	{
		event_not_found(command);
		return (0);
	}
	return (1);
}

int			get_d_bang(char *command, int *a, char **result,
			t_control **history)
{
	int		b;

	(void)command;
	b = 0;
	if (!(*history) || (*history)->length <= 0
			|| (!((*history)->begin) && (*history)->begin->name))
		return (0);
	while ((*history)->begin->name[b])
	{
		*result = ft_str_chr_cat(*result, (*history)->begin->name[b]);
		b++;
	}
	(*a) += 2;
	return (1);
}

int			get_n_first(char *command, int *a, char **result,
			t_control **history)
{
	int		b;
	int		nb;
	t_lst	*tmp;
	char	*test;

	b = 0;
	nb = 0;
	nb = ft_atoi(&command[1]);
	if (nb > (*history)->length || b <= 0)
		return (0);
	tmp = NULL;
	if (*history && (*history)->end)
		tmp = (*history)->end;
	while (tmp != NULL && b < nb)
	{
		tmp = tmp->prev;
		b++;
	}
	if (tmp)
	{
		b = 0;
		while (tmp->name[b])
		{
			*result = ft_str_chr_cat(*result, tmp->name[b]);
			b++;
		}
	}
	test = ft_itoa(nb);
	(*a) += ft_strlen(test);
	free(test);
	return (1);
}

int			get_n_last(char *command, int *a, char **result,
			t_control **history)
{
	int		b;
	int		nb;
	t_lst	*tmp;
	char	*test;

	b = 1;
	if (command[2] && !(ft_isdigit(command[2])))
		return (0);
	nb = ft_atoi(&command[2]);
	if (b > (*history)->length || b <= 0)
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
			*result = ft_str_chr_cat(*result, tmp->name[b]);
			b++;
		}
	}
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

	if (!(test = ft_memalloc(1)))
		return (0);
	tmp = NULL;
	b = 1;
	while (command[b] && command[b] != '!' && command[b] != ' ')
	{
		test = ft_str_chr_cat(test, command[b]);
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
			*result = ft_str_chr_cat(*result, tmp->name[b]);
			b++;
		}
	}
	else
	{
		ft_strdel(&test);
		return (0);
	}
	(*a) += ft_strlen(test) + 2;
	ft_strdel(&test);
	return (1);
}

// NEED CHECK
void		modify_quotes(int *sq, int *dq, char c, int *a)
{
	if (c == '\'')
	{
		if (*sq >= 1)
			(*sq)--;
		else if (*sq == 0)
			(*sq)++;
	}
	else if (c == '"')
	{
		if (*dq >= 1)
			(*dq)--;
		else if (*dq == 0)
			(*dq)++;
	}
	(*a)++;
}
