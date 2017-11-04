/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:16:26 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 21:20:59 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		history_s(t_control **history, char **tab, char *file)
{
	int		i;
	char	*string;

	i = 2;
	string = ft_strnew(0);
	while (tab[i])
	{
		string = ft_strapp(string, tab[i]);
		if (tab[i + 1])
			string = ft_strapp(string, " ");
		i++;
	}
	if (save_history(history, string, file) == -1)
	{
		ft_strdel(&string);
		return (0);
	}
	ft_strdel(&string);
	return (1);
}
