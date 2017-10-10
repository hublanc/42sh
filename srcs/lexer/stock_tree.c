/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 18:21:51 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/18 16:09:47 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node			*stock_separator(t_token *list, t_node *tree)
{
	while (list)
	{
		if (list->e_type == SEMI_COLON || list->e_type == ET
		|| list->e_type == OU)
			insert_right(&tree, list->e_type, list->token);
		list = list->next;
	}
	return (tree);
}

t_node			*stock_pipe(t_token *list, t_node *tree)
{
	int		depth;

	depth = 0;
	while (list)
	{
		if (list->e_type == SEMI_COLON || list->e_type == ET
		|| list->e_type == OU)
			depth++;
		else if (list->e_type == PIPE)
			insert_pipe(&tree, list->e_type, list->token, depth);
		list = list->next;
	}
	return (tree);
}

t_node			*stock_token(t_token *list, t_node *tree, int word)
{
	int			depth;
	int			pipe;

	pipe = 0;
	depth = 0;
	while (list)
	{
		if (list->e_type == SEMI_COLON || list->e_type == ET
		|| list->e_type == OU)
		{
			depth++;
			pipe = 0;
		}
		else if (list->e_type == PIPE)
			pipe++;
		else if (list->e_type == REDIRECTION && !word)
			insert_token(&tree, list, depth, pipe);
		else if (list->e_type == WORD && word)
			insert_token(&tree, list, depth, pipe);
		list = list->next;
	}
	return (tree);
}

t_node			*create_tree(t_token *list)
{
	t_node		*tree;
	t_token		*tmp;
	int			depth;

	tree = NULL;
	if (!list)
		return (tree);
	tree = stock_separator(list, tree);
	tree = stock_pipe(list, tree);
	tree = stock_token(list, tree, 0);
	tree = stock_token(list, tree, 1);
	tmp = list;
	depth = 0;
	return (tree);
}
