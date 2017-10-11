/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:42:56 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/11 20:21:05 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token			*new_token(char *token, int type)
{
	t_token			*new;

	if (!(new = (t_token*)ft_memalloc(sizeof(struct s_token))))
		return (NULL);
	if (token)
		new->token = ft_strdup(token);
	new->e_type = type;
	new->next = NULL;
	return (new);
}

void			add_token(t_token **list, t_token *new)
{
	if (*list)
	{
		while (*list)
			list = &(*list)->next;
		*list = new;
	}
	else
		*list = new;
}

void			delone_token(t_token **list)
{
	if (!list)
		return ;
	ft_strdel(&(*list)->token);
	free(*list);
	*list = NULL;
}

void			del_token(t_token **list)
{
	if (*list)
	{
		del_token(&(*list)->next);
		delone_token(&(*list));
	}
}

t_token			*destroy_one(t_token *list, t_token *cur)
{
	t_token		*prev;

	if (!list || !cur)
		return (list);
	prev = list;
	if (cur && cur == prev)
	{
		list = prev->next;
		delone_token(&prev);
		return (list);
	}
	while (prev)
	{
		if (prev->next == cur)
		{
			prev->next = cur->next;
			delone_token(&cur);
			return (list);
		}
		prev = prev->next;
	}
	return (list);
}
