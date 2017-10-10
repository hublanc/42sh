/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:26:10 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/06 14:06:56 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			do_built_in(char **tab, char ***env, t_control **his)
{
	int		status;

	status = 0;
	if (ft_strcmp(tab[0], "exit") == 0)
		stop_shell(env, tab, his);
	else if (ft_strcmp(tab[0], "echo") == 0)
		status = ft_echo(tab);
	else if (ft_strcmp(tab[0], "setenv") == 0)
		status = ft_setenv(tab, env);
	else if (ft_strcmp(tab[0], "unsetenv") == 0)
		status = ft_unsetenv(tab, env);
	else if (ft_strcmp(tab[0], "env") == 0)
		status = ft_env(*env, tab);
	else if (ft_strcmp(tab[0], "cd") == 0)
		status = ft_cd(tab, env);
	else if (ft_strcmp(tab[0], "history") == 0)
		status = ft_history(tab, env, his);
	return (status);
}

int			exec_builtin_pipe(t_node *tree, char **tab,
			char ***env, t_control **his)
{
	pid_t	son;

	son = fork();
	if (!son)
	{
		prep_fd(tree);
		do_built_in(tab, env, his);
		exit(0);
	}
	return (0);
}

int			exec_builtin(t_node *tree, char **tab, char ***env, t_control **his)
{
	int		outholder;
	int		inholder;
	int		status;

	inholder = fcntl(0, F_GETFD) < 0 ? -1 : dup(0);
	outholder = fcntl(1, F_GETFD) < 0 ? -1 : dup(1);
	prep_fd(tree);
	status = do_built_in(tab, env, his);
	if (outholder != -1)
		dup2(outholder, 1);
	if (inholder != -1)
		dup2(inholder, 0);
	close(inholder);
	close(outholder);
	return (status);
}

int			built_in(t_node *tree, char **tab, char ***env, t_control **his)
{
	int		status;

	if (tree->pipe || tree->end_pipe)
	{
		g_is_child = 1;
		status = exec_builtin_pipe(tree, tab, env, his);
		g_is_child = 0;
	}
	else
		status = exec_builtin(tree, tab, env, his);
	return (status);
}

int			builtin_tab(char **tab)
{
	if (!ft_strcmp(tab[0], "exit") || !ft_strcmp(tab[0], "echo")
	|| !ft_strcmp(tab[0], "setenv") || !ft_strcmp(tab[0], "unsetenv")
	|| !ft_strcmp(tab[0], "env") || !ft_strcmp(tab[0], "cd")
	|| !ft_strcmp(tab[0], "history"))
		return (1);
	else
		return (0);
}
