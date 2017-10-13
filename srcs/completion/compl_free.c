/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 11:34:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/28 14:52:09 by amazurie         ###   ########.fr       */
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
		free(tabl[i++]);
	free(tabl);
}

static void	compl_freeargs(t_coargs *args)
{
	t_coargs *ar;

	if (!args)
		return ;
	(args->arg) ? free(args->arg) : 0;
	args = args->next;
	while (args)
	{
		(args->arg) ? free(args->arg) : 0;
		ar = args;
		args = args->next;
		free(ar);
	}
}

void		compl_free(t_compl *compl)
{
	(compl->path) ? free(compl->path) : 0;
	(compl->arg) ? free(compl->arg) : 0;
	compl_freeargs(&compl->args);
	signal(SIGINT, &get_signal);
}
