/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 18:02:23 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/20 18:07:26 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		operator_or(t_node *tree)
{
	int		*status;
	t_node	*tmp;

	status = singleton_status();
	tmp = tree;
	if (tmp->right && tmp->right->value >= 5)
	{
		tmp = tmp->right;
		if (tmp->left && *status == 0)
			tmp->left->do_it = 1;
	}
	else if (tmp->right && *status == 0)
		tmp->right->do_it = 1;
}

void		operator_and(t_node *tree)
{
	int		*status;
	t_node	*tmp;

	status = singleton_status();
	tmp = tree;
	if (tmp->right && tmp->right->value >= 5)
	{
		tmp = tmp->right;
		if (tmp->left && *status != 0)
			tmp->left->do_it = 1;
	}
	else if (tmp->right && *status != 0)
		tmp->right->do_it = 1;
}

void		pipe_flag(t_node *tree)
{
	t_node	*tmp;

	tmp = tree->left;
	if (tmp->value == 1)
		tmp->pipe = 1;
	else if (tmp->value == 3)
	{
		while (tmp->left && tmp->value != 1)
			tmp = tmp->left;
		if (tmp->value == 1)
			tmp->pipe = 1;
	}
}

void		end_flag(t_node *tree)
{
	t_node	*tmp;

	tmp = tree->right;
	if (tmp->value == 1)
		tmp->end_pipe = 1;
	else if (tmp->value == 3)
	{
		while (tmp->left && tmp->value != 1)
			tmp = tmp->left;
		if (tmp->value == 1)
			tmp->end_pipe = 1;
	}
}

void		wait_flag(t_node *tree)
{
	t_node	*tmp;

	tmp = tree;
	while (tmp->right && tmp->value == 4)
		tmp = tmp->right;
	while (tmp->left && tmp->value != 1)
		tmp = tmp->left;
	if (tmp)
		tmp->wait = 1;
}
