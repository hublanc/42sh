/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 11:03:53 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/05 17:23:02 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			print_error(int err, char *cmd)
{
	if (err == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	else if (err == 2)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmd, 2);
	}
	else if (err == 8)
	{
		ft_putstr_fd("shell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ambiguous redirect", 2);
	}
	(err == 3) ? ft_putstr_fd("cd: HOME not set", 2) : 0;
	(err == 4) ? ft_putstr_fd(cmd, 2) : 0;
	(err == 4) ? ft_putstr_fd(": Permission denied", 2) : 0;
	(err == 5) ? ft_putstr_fd("Invalid argument", 2) : 0;
	(err == 6) ? ft_putstr_fd("cd : OLDPWD not set", 2) : 0;
	(err == 7) ? ft_putstr_fd("usage: unsetenv Key", 2) : 0;
	ft_putchar_fd('\n', 2);
	return (1);
}

void		print_usage(char c)
{
	ft_putstr_fd("illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: env [-i] [-u name] [name=value ...]", 2);
	ft_putstr_fd(" [utility[argument ...]]\n", 2);
}

int			check_access(char *path)
{
	int		res;

	res = 1;
	if (access(path, F_OK) == -1)
		res = -1;
	if (res != -1 && access(path, X_OK) == -1)
		res = -2;
	return (res);
}

int			pwdnotset(char ***env)
{
	char		*new[2];
	int			pos;

	new[0] = "setenv";
	new[1] = get_elem(env, "PWD=");
	ft_setenv(new, env);
	pos = in_env("PWD", *env);
	return (pos);
}

/*
** May need to be in print_error
*/

void		event_not_found(char *str)
{
	int		i;

	i = 0;
	ft_putstr("shell: event not found: ");
	while (str[i] && str[i] != ' ')
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putchar('\n');
}
