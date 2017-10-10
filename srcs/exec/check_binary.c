/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 15:49:45 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/28 18:48:12 by hublanc          ###   ########.fr       */
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

int			find_binary(char **args, char **env, char **cmd)
{
	char		**bin;
	int			access;
	int			i;

	access = 0;
	i = 0;
	if (ft_strchr(args[0], '/'))
		return (check_access(args[0]));
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
	}
	if (ret == -1)
		return (127);
	else if (ret == -2)
		return (126);
	return (0);
}
