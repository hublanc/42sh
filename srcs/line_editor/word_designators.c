/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:53:30 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/01 16:16:26 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*wd_designator(char *command, t_control **history)
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

static int	wd_designator_2(char *command, int *a, char **result,
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

static int	wd_designator_3(char *command, int *a, char **result,
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

static int	wd_designator_4(char *command, int *a, char **result,
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

static int	wd_designator_5(char *command, int *a, char **result,
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
