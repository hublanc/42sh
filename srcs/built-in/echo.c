/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:12:29 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/01 14:57:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_echo(char **tab)
{
	int		i;
	int		nl;

	i = 1;
	nl = 1;
	if (fcntl(STDOUT_FILENO, F_GETFD) < 0)
	{
		ft_putstr_fd("echo: write error: Bad file descriptor\n", 2);
		return (1);
	}
	if (len_array(tab) > 1)
	{
		nl = !ft_strcmp("-n", tab[1]) ? 0 : 1;
		i += !ft_strcmp("-n", tab[1]) ? 1 : 0;
		while (tab[i])
		{
			ft_putstr(tab[i]);
			if (tab[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	if (nl)
		ft_putchar('\n');
	return (0);
}
