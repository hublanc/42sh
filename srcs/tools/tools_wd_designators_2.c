/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_wd_designators_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 23:10:45 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/01 23:10:47 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		atoi_free(int *digit, char **test)
{
	(*digit) = ft_atoi(*test);
	ft_strdel(test);
}

void		append_in_result(t_bang **bang, char *to_append)
{
	int		i;

	i = 0;
	while (to_append[i])
	{
		(*bang)->result = ft_str_chr_cat((*bang)->result, to_append[i]);
		i++;
	}
}

int			return_cond(t_bang **bang, int a, t_lst *tmp)
{
	if (tmp)
		(*bang)->to_append = ft_strdup(tmp->name);
	else
		return (hist_event_not_found(bang, a));
	return (1);
}

int			hist_event_not_found(t_bang **bang, int a)
{
	ft_putstr("shell: ");
	while ((*bang)->command[a])
		ft_putchar((*bang)->command[a++]);
	ft_putendl(": event_not_found");
	return (0);
}

int			tablen(char **tab)
{
	int		a;

	a = 0;
	while (tab[a])
		a++;
	return (a);
}