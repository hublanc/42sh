/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_wd_designators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:19:22 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/02 13:32:03 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		is_quote(t_bang **bang)
{
	if ((*bang)->quotes == 0)
		(*bang)->quotes = 1;
	else if ((*bang)->quotes == 1)
		(*bang)->quotes = 0;
	((*bang)->index)++;
}

int			error_unrecognized_hmod(t_bang **bang, char **test, int a)
{
	ft_putstr("shell: ");
	ft_putstr(&(*bang)->command[a]);
	ft_putendl(": unrecognized history modifier");
	ft_strdel(test);
	return (0);
}

int			error_bad_wspec(int digit, char ***splitted)
{
	ft_putstr("shell: :");
	ft_putnbr(digit);
	ft_putendl(": bad word specifier");
	digit = 0;
	while ((*splitted)[digit])
	{
		ft_strdel(&(*splitted)[digit]);
		digit++;
	}
	free(*splitted);
	return (0);
}

int			malloc_struct_bang(t_bang **bang, char *command)
{
	if (!((*bang) = ft_memalloc(sizeof(t_bang))))
		return (0);
	(*bang)->result = NULL;
	(*bang)->to_append = NULL;
	if (((*bang)->command = ft_strdup(command)) == NULL)
		return (0);
	(*bang)->index = 0;
	(*bang)->len = ft_strlen(command);
	(*bang)->quotes = 0;
	return (1);
}

void		free_struct_bang(t_bang **bang)
{
	ft_strdel(&(*bang)->result);
	ft_strdel(&(*bang)->to_append);
	ft_strdel(&(*bang)->command);
	free(*bang);
	bang = NULL;
}
