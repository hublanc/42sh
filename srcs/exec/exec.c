/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:13:08 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/06 12:10:55 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_exec(char *cmd, char **args, char **env)
{
	char		**bin;
	int			i;

	i = 0;
	if (ft_strchr(args[0], '/'))
		execve(args[0], args, env);
	else if (cmd)
		execve(cmd, args, env);
	del_tabstr(&bin);
	exit(EXIT_FAILURE);
}

int			check_cmd(char **tab, char **env, t_node *tree)
{
	pid_t		son;
	int			status;
	char		*cmd;

	cmd = NULL;
	status = check_binary(tab, env, &cmd);
	if (status == 126 || status == 127)
		return (status);
	son = fork();
	if (son == 0)
	{
		prep_fd(tree);
		if (tree->in_pipe != 0)
			close(tree->in_pipe);
		ft_exec(cmd, tab, env);
	}
	if (son && tree->in == 0 && tree->out == 1)
		waitpid(son, &status, WUNTRACED | WCONTINUED);
	ft_strdel(&cmd);
	return (status);
}

void		get_cmd(t_node *tree, char ***env, int *status, t_control **his)
{
	int		i;
	char	**tab;

	i = 0;
	tab = ft_cmdsplit(tree->token);
	if (!tree->token || *(tree->token) == '\0' || !tab || !*tab)
		return (del_tabstr(&tab));
	if (builtin_tab(tab))
		*status = built_in(tree, tab, env, his);
	else
	{
		g_is_child = 1;
		*status = check_cmd(tab, *env, tree);
		g_is_child = 0;
	}
	del_tabstr(&tab);
}
