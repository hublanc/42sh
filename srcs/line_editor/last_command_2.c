/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 14:27:32 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/26 16:03:17 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		set_error(int a, char *command)
{
	int		b;

	b = 0;
	if (a == 1)
	{
		ft_putendl("shell: syntax error near unexpected token `newline'");
	}
	else if (a == 2)
	{
		ft_putstr("shell : s:");
		while (command[b] && command[b] != ' ')
		{
			ft_putchar(command[b]);
			b++;
		}
		ft_putendl(": substitution failed");
	}
}

int			get_d_bang(char *command, char **str, t_control **history,
			int *index)
{
	int		a;

	a = 0;
	if (!(*history) || (*history)->length <= 0
			|| (!((*history)->begin && (*history)->begin->name)))
		return (0);
	while ((*history)->begin->name[a])
	{
		*str = ft_str_chr_cat(*str, (*history)->begin->name[a]);
		a++;
	}
	*str = ft_str_chr_cat(*str, ' ');
	a = 0;
	while (command && command[a] && command[a] != ' ')
		a++;
	(*index) += a;
	return (1);
}

void		modify_quotes(int *sq, int *dq, char c)
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
}

int			is_d_dot(char *str)
{
	int		a;

	a = 0;
	while (str[a] && str[a] != ' ')
	{
		if (str[a] == ':')
			return (1);
		a++;
	}
	return (0);
}
