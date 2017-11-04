/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:26:44 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 19:32:45 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		init_substi1(int *i, int *k, char *old, int j)
{
	*i = 0;
	*k = j * ft_strlen(old);
}

void		init_substi2(int *j, int *l, char *arg)
{
	*j = 0;
	*l = ft_strlen(arg);
}

void		init_substi3(int *i, int *j, int *l, char *arg)
{
	*i = 0;
	*j = 0;
	*l = ft_strlen(arg);
}

void		loop_substi(int *i, int *j, char *old)
{
	*i += ft_strlen(old);
	(*j)++;
}
