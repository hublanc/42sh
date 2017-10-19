/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:47:59 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/19 21:48:36 by hublanc          ###   ########.fr       */
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

int			print_alloc_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int			error_env(size_t *i)
{
	free(i);
	return (1);
}

void		end_ft_env(size_t *i, char **env)
{
	if (i[2])
		env_tab(env);
	free(i);
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
