/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:08:10 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/31 14:10:11 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		node_print(t_node *this, int current_level, int max_level)
{
	int i;

	i = 0;
	if (this)
	{
		node_print(this->right, current_level + 1, max_level);
		while (i++ < current_level)
			ft_putstr("    ");
		ft_putendl(this->token);
		node_print(this->left, current_level + 1, max_level);
	}
	else
	{
		if (current_level < max_level)
		{
			node_print(NULL, current_level + 1, max_level);
			while (i++ < current_level)
				ft_putstr("    ");
			ft_putendl("..");
			node_print(NULL, current_level + 1, max_level);
		}
	}
}

void		extra_check_word(t_token *list, t_token *tmp, t_token **next)
{
	t_token		*del;

	del = *next;
	tmp->token = ft_strapp(tmp->token, " ");
	tmp->token = ft_strapp(tmp->token, del->token);
	*next = del->next;
	list = destroy_one(list, del);
}

t_token		*get_prev(t_token *list, t_token *cur)
{
	t_token	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (tmp)
	{
		if (tmp->next && tmp->next == cur)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		display_token(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (!list)
		return ;
	while (tmp)
	{
		ft_putendl(tmp->token);
		tmp = tmp->next;
	}
}

t_token		*abort_lexer(t_token *list, char **cmd, char *error)
{
	ft_putstr_fd("parse error near ", 2);
	ft_putendl_fd(error, 2);
	del_token(&list);
	*cmd = NULL;
	return (list);
}
