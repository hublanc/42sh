/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_wd_designators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:19:22 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/06 03:02:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	atoi_free(int *digit, char **test)
{
	(*digit) = ft_atoi(*test);
	ft_strdel(test);
}

int		tablen(char **tab)
{
	int	a;

	a = 0;
	while (tab[a])
		a++;
	return (a);
}

int		error_bad_wspec(int digit, char ***splitted)
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
