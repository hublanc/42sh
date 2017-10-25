/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:47:59 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/25 12:26:10 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	hand_u(char *uelem, char ***envcpy, size_t *i)
{
	char		**tmp;

	if (!uelem)
	{
		ft_putstr_fd("env: option requires an arguments -- u\n", 2);
		ft_putstr_fd("usage [-i] [-u name] [utility [arguments]]\n", 2);
		i[2] = 0;
		return (1);
	}
	else if (ft_strchr(uelem, '='))
	{
		ft_putstr_fd("env: unsetenv ", 2);
		ft_putstr_fd(uelem, 2);
		ft_putstr_fd(": Invalid argument\n", 2);
		i[2] = 0;
		return (1);
	}
	else
	{
		tmp = delonenv(uelem, *envcpy);
		del_tabstr(envcpy);
		*envcpy = tmp;
		return (0);
	}
}

int			builtu_env(char **lstav, char ***envcpy, size_t *i)
{
	int		stat;

	if (lstav[i[0]][i[1] + 1])
	{
		stat = hand_u((lstav[i[0]] + ft_strlen_chr(lstav[i[0]], 'u') + 1),
				envcpy, i);
		i[1] = ft_strlen(lstav[i[0]]);
	}
	else if (lstav[i[0] + 1])
		stat = hand_u(lstav[++i[0]], envcpy, i);
	else
	{
		stat = hand_u(NULL, envcpy, i);
		i[2] = 0;
	}
	i[3] = 1;
	return (stat);
}

static void	ft_envexec(char *cmd, char **args, char **env)
{
	int			i;

	i = 0;
	if (ft_strchr(args[0], '/'))
		execve(args[0], args, env);
	else if (cmd)
		execve(cmd, args, env);
	exit(EXIT_SUCCESS);
}

int			check_envcmd(char **tab, char **env, char **originenv)
{
	pid_t		son;
	int			status;
	char		*cmd;

	cmd = NULL;
	status = check_binary(tab, originenv, &cmd);
	if (status == 126 || status == 127)
		return (status);
	son = fork();
	if (son == 0)
		ft_envexec(cmd, tab, env);
	else
		waitpid(son, &status, WUNTRACED | WCONTINUED);
	ft_strdel(&cmd);
	return (status);
}
