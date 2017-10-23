/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:21:36 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/23 10:23:28 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	built_env(char **lstav, char ***envcpy, size_t *i)
{
	i[1] = 0;
	while (lstav[i[0]] && lstav[i[0]][++i[1]] && lstav[i[0]][0] == '-')
	{
		if (lstav[i[0]][i[1]] == 'i')
			del_tabstr(envcpy);
		else if (lstav[i[0]][i[1]] == 'u')
		{
			if (builtu_env(lstav, envcpy, i) == 1)
				return (1);
			i[1] = ft_strlen(lstav[i[0]]) - 1;
		}
		else if (lstav[i[0]][i[1]])
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(lstav[i[0]][i[1]], 2);
			ft_putstr_fd("\nusage [-i] [-u name] [utility [arguments]]\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	envexec(char **lstav, char ***envcpy, t_control **hist, size_t *i)
{
	char	**tmp;

	if ((tmp = (char **)ft_memalloc(sizeof(char *) * 3)) == NULL)
		return (print_alloc_error("allocation error"));
	if ((tmp[1] = ft_strdup(lstav[i[0]++])) == NULL)
		return (print_alloc_error("allocation error"));
	while (lstav[i[0]])
	{
		if ((tmp[0] = ft_strjoin(tmp[1], " ")) == NULL)
			return (print_alloc_error("allocation error"));
		free(tmp[1]);
		if ((tmp[1] = ft_strjoin(tmp[0], lstav[i[0]++])) == NULL)
			return (print_alloc_error("allocation error"));
		free(tmp[0]);
	}
	routine(tmp[1], envcpy, hist);
	free(tmp[1]);
	free(tmp);
	i[2] = 0;
	i[0]--;
	return (return_status());
}

static int	env_set(char *name_value, char ***env)
{
	int			stat;
	char		*name;
	char		*val;
	char		**tab;

	tab = NULL;
	if (name_value[0] == '=')
	{
		ft_putstr_fd("env: setenv: ", 2);
		ft_putstr_fd(name_value, 2);
		ft_putstr_fd(" Invalid argument", 2);
		return (1);
	}
	name = ft_strsub(name_value, 0, ft_strchr(name_value, '=') - name_value);
	val = ft_strsub(name_value, ft_strchr(name_value, '=') - name_value + 1,
		ft_strlen(name_value) - (ft_strchr(name_value, '=') - name_value));
	tab = prep_setenv(name, val);
	if (tab == NULL)
		return (1);
	stat = ft_setenv(tab, env);
	ft_strdel(&name);
	ft_strdel(&val);
	del_tabstr(&tab);
	return (stat);
}

static int	ft_env2(char **lstav, char ***envcpy, t_control **hist)
{
	size_t		*i;
	int			status;

	status = 0;
	if ((i = (size_t *)ft_memalloc(sizeof(size_t) * 6)) == NULL)
		return (1);
	i[0] = 0;
	i[2] = 1;
	i[4] = 1;
	while (lstav[++i[0]])
	{
		i[3] = 0;
		if (built_env(lstav, envcpy, i) == 1)
			return (error_env(i));
		!lstav[i[0]][1] && lstav[i[0]][0] == '-' ? del_tabstr(envcpy) : 0;
		if (!i[3] && ft_strchr(lstav[i[0]], '=')
			&& (env_set(lstav[i[0]], envcpy)) == 1)
			return (error_env(i));
		else if (i[4] == 1 && lstav[i[0]] && lstav[i[0]][0] != '-'
				&& (!ft_strchr(lstav[i[0] - 1], 'u')
				|| lstav[i[0] - 1][ft_strlen_chr(lstav[i[0] - 1], 'u') + 1]))
			status = envexec(lstav, envcpy, hist, i);
	}
	end_ft_env(i, *envcpy);
	return (status);
}

int			ft_env(char **lstav, char **env, t_control **hist)
{
	char		**envcpy;
	int			status;

	envcpy = NULL;
	if (!lstav[1])
		return (env_tab(env));
	else
	{
		if ((envcpy = get_env(env, 1)) == NULL)
			return (print_alloc_error("allocation error"));
		status = ft_env2(lstav, &envcpy, hist);
		chdir(get_elem(&env, "PWD"));
		del_tabstr(&envcpy);
	}
	return (status);
}
