/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:13:08 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:41:05 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	ft_exec(char *cmd, char **args, char **env)
{
	int			i;

	i = 0;
	if (ft_strchr(args[0], '/'))
		execve(args[0], args, env);
	else if (cmd)
		execve(cmd, args, env);
	exit(EXIT_SUCCESS);
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
		if (prep_fd(tree) != -1)
		{
			tree->in_pipe != 0 ? close(tree->in_pipe) : 0;
			ft_exec(cmd, tab, env);
		}
		tree->in_pipe != 0 ? close(tree->in_pipe) : 0;
		exit(EXIT_FAILURE);
	}
	if (son && (tree->pipe || tree->end_pipe))
		fetch_pid(son);
	else if (son)
		waitpid(son, &status, WUNTRACED | WCONTINUED);
	ft_strdel(&cmd);
	return (status);
}

void		get_cmd(t_node *tree, char ***env, int *status, t_control **his)
{
	char	**tab;

	substitution(&tree->token, 0);
	if (gest_loc(&tree->token))
		return ;
	tab = ft_cmdsplit(tree->token);
	if (!tree->token || *(tree->token) == '\0' || !tab || !*tab)
		return (del_tabstr(&tab));
	if (builtin_tab(tab[0]))
		*status = built_in(tree, tab, env, his);
	else
	{
		g_is_child = 1;
		*status = check_cmd(tab, *env, tree);
		g_is_child = 0;
	}
	del_tabstr(&tab);
}
