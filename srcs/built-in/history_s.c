/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 21:16:26 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/04 21:20:59 by lbopp            ###   ########.fr       */
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

void	init_cd_flags(t_hist_flags *flags)
{
	flags->c = 0;
	flags->d = 0;
	flags->a = 0;
	flags->n = 0;
	flags->r = 0;
	flags->w = 0;
	flags->p = 0;
	flags->s = 0;
	flags->t = 0;
}
