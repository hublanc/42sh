/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:20:15 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:41:36 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

void			destroy_leaf(t_node * leaf)
{
	if (leaf->token)
		ft_strdel(&(leaf->token));
	if (leaf->aggre_in_nb)
		free(leaf->aggre_in_nb);
	if (leaf->aggre_in_w)
		del_tabstr(&(leaf->aggre_in_w));
	if (leaf->aggre_out_nb)
		free(leaf->aggre_out_nb);
	if (leaf->aggre_out_w)
		del_tabstr(&(leaf->aggre_out_w));
	if (leaf->heredoc_str)
		ft_strdel(&(leaf->heredoc_str));
	if (leaf->fd_out)
		free(leaf->fd_out);
	if (leaf->fd_out_io)
		free(leaf->fd_out_io);
	if (leaf->fd_in)
		free(leaf->fd_in);
	if (leaf->fd_in_io)
		free(leaf->fd_in_io);
}

void			destroy_tree(t_node *leaf)
{
	if (leaf)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		destroy_leaf(leaf);
		free(leaf);
	}
}

void			insert_token(t_node **leaf, t_token *tk, int depth, int pipe)
{
	if (!*leaf)
	{
		*leaf = (t_node*)ft_memalloc(sizeof(struct s_node));
		(*leaf)->value = tk->e_type;
		if (tk->token)
			(*leaf)->token = ft_strdup(tk->token);
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	}
	else if (depth > 0)
		insert_token(&(*leaf)->right, tk, depth - 1, pipe);
	else if ((*leaf)->value == 5)
		insert_token(&(*leaf)->left, tk, depth, pipe);
	else if (pipe > 0)
		insert_token(&(*leaf)->right, tk, depth, pipe - 1);
	else if ((*leaf)->value >= (int)tk->e_type)
		insert_token(&(*leaf)->left, tk, depth, pipe);
	else if ((*leaf)->value < (int)tk->e_type)
		insert_token(&(*leaf)->right, tk, depth, pipe);
}

void			insert_right(t_node **leaf, int value, char *token)
{
	if (!*leaf)
	{
		*leaf = (t_node*)ft_memalloc(sizeof(struct s_node));
		(*leaf)->value = value;
		if (token)
			(*leaf)->token = ft_strdup(token);
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	}
	else
		insert_right(&(*leaf)->right, value, token);
}

void			insert_pipe(t_node **leaf, int value, char *token, int depth)
{
	if (!*leaf)
	{
		*leaf = (t_node*)ft_memalloc(sizeof(struct s_node));
		(*leaf)->value = value;
		if (token)
			(*leaf)->token = ft_strdup(token);
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	}
	else if (depth > 0)
		insert_pipe(&(*leaf)->right, value, token, depth - 1);
	else if ((*leaf)->value == 5)
		insert_pipe(&(*leaf)->left, value, token, depth);
	else if ((*leaf)->value == 4)
		insert_pipe(&(*leaf)->right, value, token, depth);
}

void			node_print(t_node *this, int current_level, int max_level)
{
	int i;

	if (this)
	{
		node_print(this->right, current_level + 1, max_level);
		for (i = 0; i < current_level; i++)
			printf("    ");
		printf("%s\n", this->token);
		node_print(this->left, current_level + 1, max_level);
	} 
	else
	{
		if (current_level < max_level)
		{
			node_print(NULL, current_level + 1, max_level);
			for (i = 0; i < current_level; i++)
				printf("    ");
			printf("..\n");
			node_print(NULL, current_level + 1, max_level);
		}
	}
}
