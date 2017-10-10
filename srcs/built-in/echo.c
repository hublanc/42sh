/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:12:29 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/27 19:06:34 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_echo(char **tab)
{
	int		i;

	i = 1;
	if (fcntl(STDOUT_FILENO, F_GETFD) < 0)
	{
		ft_putstr_fd("echo: write error: Bad file descriptor\n", 2);
		return (1);
	}
	if (len_array(tab) > 1)
	{
		while (tab[i])
		{
			ft_putstr(tab[i]);
			if (tab[i + 1])
				ft_putchar(' ');
			i++;
		}
	}
	ft_putchar('\n');
	return (0);
}
