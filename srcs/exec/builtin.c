/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:26:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 14:45:20 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	do_built_in(char **tab, char ***env, t_control **his)
{
	int		status;

	status = 0;
	if (ft_strcmp(tab[0], "exit") == 0)
		status = stop_shell(env, tab, his);
	else if (ft_strcmp(tab[0], "echo") == 0)
		status = ft_echo(tab);
	else if (ft_strcmp(tab[0], "setenv") == 0)
		status = ft_setenv(tab, env);
	else if (ft_strcmp(tab[0], "unsetenv") == 0)
		status = ft_unsetenv(tab, env);
	else if (ft_strcmp(tab[0], "env") == 0)
		status = ft_env(tab, *env, his);
	else if (ft_strcmp(tab[0], "cd") == 0)
		status = ft_cd(tab, env);
	else if (ft_strcmp(tab[0], "history") == 0)
		status = ft_history(tab, env, his);
	else if (ft_strcmp(tab[0], "read") == 0)
		status = ft_read(tab + 1);
	else if (ft_strcmp(tab[0], "unset") == 0)
		status = unset(tab, env);
	else if (ft_strcmp(tab[0], "export") == 0)
		status = export(tab, env);
	status = (!ft_strcmp(tab[0], "hash")) ? hash_built(tab, *env) : status;
	return (status);
}

static int	exec_builtin_pipe(t_node *tree, char **tab,
			char ***env, t_control **his)
{
	pid_t	son;

	son = fork();
	if (!son)
	{
		prep_fd(tree);
		if (!ft_strcmp(tab[0], "exit"))
			exit(0);
		do_built_in(tab, env, his);
		exit(0);
	}
	fetch_pid(son);
	return (0);
}

static int	exec_builtin(t_node *tree, char **tab, char ***env, t_control **his)
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
	|| !ft_strcmp(tab[0], "history") || !ft_strcmp(tab[0], "unset")
	|| !ft_strcmp(tab[0], "export") || !ft_strcmp(tab[0], "read")
	|| !ft_strcmp(tab[0], "hash"))
		return (1);
	else
		return (0);
}
