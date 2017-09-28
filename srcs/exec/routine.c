/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:10:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/14 18:34:37 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		exec_cmd(t_node *tree, char ***env, t_control **hist)
{
	static int		input = 0;
	static int		fd[2] = {0, 1};
	int				signal;

	signal = 0;
	if (tree->pipe)
		pipe(fd);
	else if (tree->end_pipe)
		fd[1] = 1;
	else if (!tree->fd_out && !tree->fd_in)
	{
		input = 0;
		fd[0] = 0;
		fd[1] = 1;
	}
	tree->in = input;
	tree->out = fd[1];
	tree->in_pipe = fd[0];
	get_cmd(tree, env, &signal, hist);
	fd[1] != 1 ? close(fd[1]) : 0;
	input != 0 ? close(input) : 0;
	if (tree->pipe)
		input = fd[0];
	if (tree->end_pipe)
	{
		input != 0 ? close(input) : 0;
		fd[0] != 0 ? close(fd[0]) : 0;
		input = 0;
		fd[0] = 0;
		fd[1] = 1;
	}
}

void		wait_flag(t_node *tree)
{
	t_node		*tmp;

	tmp = tree;
	while (tmp->right && tmp->value == 4)
		tmp = tmp->right;
	while (tmp->left && tmp->value != 1)
		tmp = tmp->left;
	if (tmp)
		tmp->wait = 1;
}

void		end_flag(t_node *tree)
{
	t_node		*tmp;

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

void		pipe_flag(t_node *tree)
{
	t_node		*tmp;

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

void		hub(t_node *tree, char ***env, t_control **hist)
{
	static int		pid_w = 0;

	if (tree->value == 1)
		exec_cmd(tree, env, hist);
	if (tree->wait)
	{
		while (pid_w-- > 0)
			wait(NULL);
		pid_w = 0;
	}
	if (tree->value == 4 && tree->right)
	{
		pipe_flag(tree);
		end_flag(tree);
		wait_flag(tree);
		pid_w += (tree->right->value != 4) ? 2 : 1;
	}
	tree->value != 3 ? close_fd(tree) : 0;
	tree->value == 3 ? manage_fd(tree) : 0;
}

void		exec_tree(t_node *tree, char ***env, t_control **hist)
{
	if (!tree)
		return ;
	if (tree->value != 5)
		hub(tree, env, hist);
	exec_tree(tree->left, env, hist);
	exec_tree(tree->right, env, hist);
}

void		routine(char *cmd, char ***env, t_control **history)
{
	t_token		*list;
	t_node		*tree;
	char		*new_command;

	new_command = last_command(cmd, history);	
//	change cmd with ! by old cmd
//	list = tokenizer(cmd);
	list = tokenizer(new_command);
	list = sort_token(list, history);
	if (!list)
		return ((void)print_prompt());
	tree = create_tree(list);
	reset_term();
	node_print(tree, 0, 3);
	exec_tree(tree, env, history);
	set_terminal();
	del_token(&list);
	destroy_tree(tree);
	print_prompt();
}
