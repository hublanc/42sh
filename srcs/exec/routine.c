/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:10:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/10 18:16:18 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			*singleton_status(void)
{
	static int		status = 0;

	return (&status);
}

void		check_status(int status)
{
	if (status == 6 || status == 10 || status == 11)
	{
		ft_putstr_fd("Program has encounter a problem: ", 2);
		get_signal(status);
	}
	else if (status == 2)
		ft_putchar('\n');
}

void		exec_cmd(t_node *tree, char ***env, t_control **hist)
{
	static int		input = 0;
	static int		fd[2] = {0, 1};
	int				*signal;

	signal = singleton_status();
	if (tree->pipe)
		pipe(fd);
	else if (tree->end_pipe)
		fd[1] = 1;
	tree->in = input;
	tree->out = fd[1];
	tree->in_pipe = fd[0];
	get_cmd(tree, env, signal, hist);
	check_status(*signal);
	fd[1] != 1 ? close(fd[1]) : 0;
	input != 0 ? close(input) : 0;
	if (tree->pipe)
		input = fd[0];
	if (tree->end_pipe)
	{
		input = 0;
		fd[0] = 0;
		fd[1] = 1;
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
	if (tree->value < 5)
		hub(tree, env, hist);
	if (tree->left && tree->left->do_it == 0)
		exec_tree(tree->left, env, hist);
	if (tree->value == 7)
		operator_and(tree);
	else if (tree->value == 8)
		operator_or(tree);
	if (tree->right && tree->right->do_it == 0)
		exec_tree(tree->right, env, hist);
}

void		routine(char *cmd, char ***env, t_control **history)
{
	t_token		*list;
	t_node		*tree;
	char		*new_command;

	new_command = wd_designator(cmd, history);
	list = tokenizer(new_command);
	list = sort_token(list, history);
	if (!list)
		return ;
	tree = create_tree(list);
	reset_term();
	node_print(tree, 0, 3);
	exec_tree(tree, env, history);
	set_terminal();
	del_token(&list);
	destroy_tree(tree);
}
