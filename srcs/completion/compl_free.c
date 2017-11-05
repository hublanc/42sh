/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 11:34:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/05 13:38:33 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		free_tabl(char **tabl)
{
	int i;

	if (!tabl)
		return ;
	i = 0;
	while (tabl[i])
		ft_strdel(&tabl[i++]);
	free(tabl);
}

static void	compl_freeargs(t_coargs *args)
{
	t_coargs *ar;

	if (!args)
		return ;
	(args->arg) ? ft_strdel(&args->arg) : 0;
	args = args->next;
	while (args)
	{
		(args->arg) ? ft_strdel(&args->arg) : 0;
		ar = args;
		args = args->next;
		free(ar);
	}
}

void		compl_free(t_compl *compl)
{
	(compl->path) ? ft_strdel(&compl->path) : 0;
	(compl->arg) ? ft_strdel(&compl->arg) : 0;
	compl_freeargs(&compl->args);
	signal(SIGINT, &get_signal);
}
