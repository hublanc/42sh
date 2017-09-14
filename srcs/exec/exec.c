/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:13:08 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/14 19:16:20 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**get_bin(char **env, int pos)
{
	char		**dup;
	char		*str;

	if (pos == -1)
		return (NULL);
	str = ft_strdup(env[pos] + 5);
	dup = ft_strsplit(str, ':');
	ft_strdel(&str);
	return (dup);
}

void		ft_exec(char **args, char **env)
{
	char		**bin;
	int			i;

	i = 0;
	if (ft_strchr(args[0], '/') && execve(args[0], args, env) == -1)
		return (err_nofordir(args[0], &args));
	bin = get_bin(env, in_env("PATH", env));
	while (bin && bin[i])
	{
		bin[i] = ft_strapp(bin[i], "/");
		bin[i] = ft_strapp(bin[i], args[0]);
		execve(bin[i++], args, env);
	}
	print_error(2, args[0]);
	del_tabstr(&args);
	del_tabstr(&bin);
	exit(EXIT_FAILURE);
}

int			check_cmd(char **tab, char **env, t_node *tree)
{
	pid_t		father;
	int			status;
	int			pid;

	status = 0;
	father = fork();
	pid = father;
	if (father == 0)
	{
		prep_fd(tree);
		if (tree->in_pipe != 0)
			close(tree->in_pipe);
		ft_exec(tab, env);
	}
	if (father)
	{
		if (tree->in == 0 && tree->out == 1)
			wait(&status);
	}
	if (status == 6 || status == 10 || status == 11)
	{
		ft_putstr_fd("PID: ", 2);
		ft_putnbr_fd(pid, 2);
	}
	if (status != 2)
		get_signal(status);
	return (status);
}

void		get_cmd(t_node *tree, char ***env, int *status, t_hist **his)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_cmdsplit(tree->token);
	if (!tree->token || *(tree->token) == '\0' || !tab || !*tab)
		return (del_tabstr(&tab));
	if (ft_strcmp(tab[0], "exit") == 0)
		stop_shell(env, tab, his);
	if (ft_strcmp(tab[0], "echo") == 0)
		ft_echo(tab);
	else if (ft_strcmp(tab[0], "setenv") == 0)
		ft_setenv(tab, env);
	else if (ft_strcmp(tab[0], "unsetenv") == 0)
		ft_unsetenv(tab, env);
	else if (ft_strcmp(tab[0], "env") == 0)
		ft_env(*env, tab);
	else if (ft_strcmp(tab[0], "cd") == 0)
		ft_cd(tab, env);
	else
	{
		g_is_child = 1;
		*status = check_cmd(tab, *env, tree);
		g_is_child = 0;
	}
	del_tabstr(&tab);
}
