/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:49:45 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/02 15:03:03 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			reset_status(void)
{
	int			*status;

	status = singleton_status();
	*status = 0;
	return (1);
}

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

static int	check_isdir(char *str)
{
	struct stat		buf;

	lstat(str, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (-3);
	}
	return (check_access(str));
}

static int	find_binary(char **args, char **env, char **cmd)
{
	char		**bin;
	int			access;
	int			i;

	access = 0;
	i = 0;
	if (ft_strchr(args[0], '/'))
		return (check_isdir(args[0]));
	else if (is_in_htable(args[0], cmd))
		return (check_access(*cmd));
	bin = get_bin(env, in_env("PATH", env));
	while (bin && bin[i] && access != -2 && access != 1)
	{
		bin[i] = ft_strapp(bin[i], "/");
		bin[i] = ft_strapp(bin[i], args[0]);
		access = check_access(bin[i]);
		if (access == 1)
			*cmd = ft_strdup(bin[i]);
		i++;
	}
	del_tabstr(&bin);
	return (access);
}

int			check_binary(char **args, char **env, char **cmd)
{
	int		ret;

	ret = find_binary(args, env, cmd);
	if (ft_strchr(args[0], '/'))
	{
		if (ret == -1)
			err_nofordir(args[0]);
		else if (ret == -2)
			print_error(4, args[0]);
	}
	else
	{
		if (ret == -1)
			print_error(2, args[0]);
		else if (ret == -2)
			print_error(4, args[0]);
		ret == 0 ? err_nofordir(args[0]) : 0;
	}
	if (ret == -1 || ret == 0)
		return (127);
	else if (ret == -2 || ret == -3)
		return (126);
	else if (ret == 1)
		add_hash_table(*cmd, args[0]);
	return (0);
}
