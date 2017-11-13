/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:47:20 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 14:23:43 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_loc			*saved_loc(t_loc *locr, int i)
{
	static t_loc	*loc = NULL;
	t_loc			*loctmp;

	if (locr)
		loc = locr;
	if (i)
	{
		while (loc)
		{
			loctmp = loc->next;
			loc->name ? ft_strdel(&loc->name) : 0;
			loc->value ? ft_strdel(&loc->value) : 0;
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
		loc->value ? ft_strdel(&loc->value) : 0;
		if (!(loc->value = ft_strdup(val)))
			loc->value = NULL;
		return ;
	}
	if (!(loc = saved_loc(NULL, 0)))
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

	if (!(loc = saved_loc(NULL, 0)) || !loc->name)
		return ;
	loctmp = NULL;
	while (loc && loc->name && ft_strcmp(loc->name, name) && (loctmp = loc))
		loc = loc->next;
	if (!loc)
		return ;
	if (!loctmp)
	{
		loc->name ? ft_strdel(&loc->name) : 0;
		loc->value ? ft_strdel(&loc->value) : 0;
		loc->name = NULL;
		loc->value = NULL;
		loc->next ? saved_loc(loc->next, 0) : 0;
		free(loc);
		return ;
	}
	loc->name ? ft_strdel(&loc->name) : 0;
	loc->value ? ft_strdel(&loc->value) : 0;
	loctmp->next = loc->next;
	free(loc);
}

t_loc			*get_loc(char *name)
{
	t_loc	*loc;

	if (!(loc = saved_loc(NULL, 0)))
		return (NULL);
	while (loc && loc->name && name && ft_strcmp(loc->name, name))
		loc = loc->next;
	if (!loc || !loc->name)
		return (NULL);
	return (loc);
}
