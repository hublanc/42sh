/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:47:59 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 13:01:13 by hublanc          ###   ########.fr       */
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

static char	**path_isnull(char **env)
{
	char	**tab;

	tab = NULL;
	if (in_env("PATH", env) != -1)
		return (NULL);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * 2)))
		return (NULL);
	tab[0] = get_path_str();
	tab[1] = NULL;
	return (tab);
}

int			check_envcmd(char **tab, char **env, char **originenv)
{
	pid_t		son;
	int			status;
	char		*cmd;
	char		**envcpy;
	t_hash		**s_hash;

	cmd = NULL;
	(void)originenv;
	s_hash = singleton_hash();
	del_hash(s_hash);
	if (!(envcpy = path_isnull(env)))
		status = check_binary(tab, env, &cmd);
	else
		status = check_binary(tab, envcpy, &cmd);
	del_tabstr(&envcpy);
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
