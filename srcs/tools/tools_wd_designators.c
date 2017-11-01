/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_wd_designators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:19:22 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/01 11:08:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			find_d_dots(char *command, int a)
{
	while (command && command[a] && command[a] != ' ')
	{
		if (command && command[a] && command[a] == ':')
			return (a);
		a++;
	}
	return (0);
}

int			tablen(char **str)
{
	int		a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

int			modified_atoi(char *str)
{
	int		a;
	char	*tmp;

	if (!(tmp = ft_memalloc(1)))
		return (0);
	a = 0;
	while (!(ft_isdigit(str[a])))
		a++;
	while (ft_isdigit(str[a]))
	{
		tmp = ft_str_chr_cat(tmp, str[a]);
		a++;
	}
	a = ft_atoi(tmp);
	ft_strdel(&tmp);
	return (a);
}

int			return_error(char *command, int index, int type)
{
	if (type == 1)
	{
		ft_putstr("shell: ");
		ft_putchar(command[index + 1]);
		ft_putendl(": bad word specifier");
	}
	else if (type == 2)
	{
		ft_putstr("shell: ");
		ft_putchar(command[index + 1]);
		ft_putendl(": unrecognized history modifier");
	}
	return (2);
}

void		set_error(int a, char *command)
{
	int		b;

	b = 0;
	if (a == 1)
		ft_putendl_fd("shell: syntax error near unexpected token `newline'", 2);
	else if (a == 2)
	{
		isatty(0) ? ft_putstr("shell : s:") : 0;
		while (command[b] && command[b] != ' ')
			isatty(0) ? ft_putchar(command[b++]) : 0;
		ft_putendl_fd(": substitution failed", 2);
	}
}
