/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:47:20 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/05 15:59:55 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_loc	*saved_loc(void)
{
	static t_loc	*loc = NULL;

	if (!loc)
	{
		if (!(loc = (t_loc *)ft_memalloc(sizeof(t_loc))))
			return (NULL);
		loc->name = NULL;
		loc->value = NULL;
		loc->next = NULL;
	}
	return (loc);
}

void		add_loc(char *name, char *val)
{
	t_loc	*loc;

	if ((loc = get_loc(name)))
	{
		(loc->value) ? free(loc->value) : 0;
		loc->value = ft_strdup(val);
		return ;
	}
	if (!(loc = saved_loc()))
		return ;
	while (loc->next && loc->name && ft_strcmp(loc->name, name))
		loc = loc->next;
	if (loc->name)
	{
		if (!(loc->next = (t_loc *)ft_memalloc(sizeof(t_loc))))
		{
			loc->next = NULL;
			return ;
		}
		loc = loc->next;
		loc->next = NULL;
		loc->name = NULL;
		loc->value = NULL;
	}
	loc->name = ft_strdup(name);
	loc->value = ft_strdup(val);
}

void		suppr_loc(char *name)
{
	t_loc	*loc;
	t_loc	*loctmp;

	if (!(loc = saved_loc()) || !loc->name)
		return ;
	loctmp = NULL;
	while (loc && loc->name && ft_strcmp(loc->name, name))
	{
		loctmp = loc;
		loc = loc->next;
	}
	if (!loc)
		return ;
	if (!loctmp)
	{
		loctmp = loc;
		loc = loc->next;
		(loctmp->name) ? free(loctmp->name) : 0;
		(loctmp->value) ? free(loctmp->value) : 0;
		free(loctmp);
		loctmp = NULL;
		return ;
	}
	loctmp->next = loc->next;
	(loc->name) ? free(loc->name) : 0;
	(loc->value) ? free(loc->value) : 0;
	free(loc);
}

t_loc		*get_loc(char *name)
{
	t_loc	*loc;

	if (!(loc = saved_loc()))
		return (NULL);
	while (loc && loc->name && ft_strcmp(loc->name, name))
		loc = loc->next;
	if (!loc || !loc->name)
		return (NULL);
	return (loc);
}
