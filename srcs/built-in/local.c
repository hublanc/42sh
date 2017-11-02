/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:47:20 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/02 14:18:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_loc			*saved_loc(int i)
{
	static t_loc	*loc = NULL;
	t_loc			*loctmp;

	if (i)
	{
		while (loc)
		{
			loctmp = loc->next;
			loc->name ? free(loc->name) : 0;
			loc->value ? free(loc->value) : 0;
			free(loc);
			loc = loctmp;
		}
	}
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

static int		add_locenv(char *name, char *val)
{
	char	***env;
	char	*tmp;
	int		i;

	env = save_env(NULL);
	if (!env || !*env || !**env)
		return (0);
	i = -1;
	while ((*env)[++i] && ft_strncmp((*env)[i], name,
				ft_strlen_chr((*env)[i], '=')))
		;
	if (!(*env)[i])
		return (0);
	free((*env)[i]);
	tmp = ft_strjoin(name, "=");
	(*env)[i] = (val) ? ft_strjoin(tmp, val) : ft_strdup(tmp);
	free(tmp);
	return (1);
}

void			add_loc(char *name, char *val)
{
	t_loc	*loc;

	if (add_locenv(name, val))
		return ;
	if ((loc = get_loc(name)))
	{
		(loc->value) ? free(loc->value) : 0;
		loc->value = ft_strdup(val);
		return ;
	}
	if (!(loc = saved_loc(0)))
		return ;
	while (loc->next && loc->name && ft_strcmp(loc->name, name))
		loc = loc->next;
	if (!loc->name)
		loc->value = ft_strdup(val);
	if (!loc->name)
		loc->name = ft_strdup(name);
	if (!loc->next && (loc->next = (t_loc *)ft_memalloc(sizeof(t_loc))))
		return ;
	loc = loc->next;
	loc->next = NULL;
	loc->name = NULL;
	loc->value = NULL;
}

void			suppr_loc(char *name)
{
	t_loc	*loc;
	t_loc	*loctmp;

	if (!(loc = saved_loc(0)) || !loc->name)
		return ;
	loctmp = NULL;
	while (loc && loc->name && ft_strcmp(loc->name, name) && (loctmp = loc))
		loc = loc->next;
	if (!loc)
		return ;
	if (!loctmp)
	{
		loctmp = loc;
		(loctmp->name) ? free(loctmp->name) : 0;
		(loctmp->value) ? free(loctmp->value) : 0;
		loctmp->name = NULL;
		loctmp->value = NULL;
		(loc->next) ? loc = loc->next : 0;
		return ;
	}
	loctmp->next = loc->next;
	(loc->name) ? free(loc->name) : 0;
	(loc->value) ? free(loc->value) : 0;
	free(loc);
}

t_loc			*get_loc(char *name)
{
	t_loc	*loc;

	if (!(loc = saved_loc(0)))
		return (NULL);
	while (loc && loc->name && name && ft_strcmp(loc->name, name))
		loc = loc->next;
	if (!loc || !loc->name)
		return (NULL);
	return (loc);
}
