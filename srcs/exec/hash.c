/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 14:53:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 10:48:25 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_hash		*new_hash(char *value, char *path, int key)
{
	t_hash		*new;

	if (!(new = (t_hash*)ft_memalloc(sizeof(struct s_hash))))
		return (NULL);
	if (value)
		new->value = ft_strdup(value);
	if (path)
		new->path = ft_strdup(path);
	new->key = key;
	new->next = NULL;
	return (new);
}

t_hash		*add_hash(t_hash *list, t_hash *new)
{
	t_hash		*tmp;

	tmp = list;
	if (list)
	{
		while (tmp->next && tmp->next->key < new->key)
			tmp = tmp->next;
		if (tmp->next)
		{
			new->next = tmp->next;
			tmp->next = new;
			return (list);
		}
		else
		{
			tmp->next = new;
			return (list);
		}
	}
	else
		return (new);
}

void		delone_hash(t_hash **list)
{
	if (!list)
		return ;
	if ((*list)->value)
		ft_strdel(&(*list)->value);
	if ((*list)->path)
		ft_strdel(&(*list)->path);
	free(*list);
	*list = NULL;
}

void		del_hash(t_hash **list)
{
	if (*list)
	{
		del_hash(&(*list)->next);
		delone_hash(&(*list));
	}
}
