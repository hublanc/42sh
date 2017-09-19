/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:35:33 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 16:46:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*int			nbr_perline(int maxlen, int w)
{
	if (w > maxlen)
		return (w / maxlen - (w % maxlen == 0));
	return (1);
}

int			nbr_percol(int nbrargs, int nbrperline)
{
	int		i;
	int		j;

	i = 0;
	while (i * nbrargs < nbrperline)
		i++;
	j = nbrargs + (nbrperline - (i - 1) * nbrargs);
	i = 0;
	while (i * nbrperline < j)
		i++;
	i--;
	j = i + (i * nbrperline < nbrargs);
	return (i + (i * nbrperline < nbrargs));
}*/

//void		print_arg(t_compl *compl, t_cmd *cmd)
//{
//}
