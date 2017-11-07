/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 20:40:01 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 16:26:04 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_exit(char **tab)
{
	int			status;

	status = return_status();
	ttyyyy(0) ? ft_putstr_fd("exit\n", 2) : 0;
	if (!tab || !*tab)
		return (status);
	if (len_array(tab) == 1)
		return (status);
	if (tab[1] && ft_strfullnb(tab[1]))
		status = ft_atoi(tab[1]);
	else
	{
		ft_putstr_fd("exit: numeric arguments required\n", 2);
		return (255);
	}
	if (len_array(tab) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (-1);
	}
	return (status);
}
