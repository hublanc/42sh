/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:21:58 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/23 10:24:44 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			in_env(char *str, char **env)
{
	char	*dup;
	int		i;

	i = 0;
	if (!str || !env)
		return (-1);
	while (*env)
	{
		dup = ft_strsub(*env, 0, ft_strchr(*env, '=') - *env);
		if (ft_strcmp(dup, str) == 0)
		{
			ft_strdel(&dup);
			return (i);
		}
		i++;
		env++;
		ft_strdel(&dup);
	}
	return (-1);
}

char		*var_app(char *name, char *value)
{
	char		*new;

	new = ft_strdup(name);
	new = ft_strapp(new, "=");
	if (value)
		new = ft_strapp(new, value);
	return (new);
}

char		**env_app(char *name, char *value, char ***env, int *status)
{
	char	**new;
	int		i;

	i = 0;
	if (ft_strchr(name, '='))
	{
		ft_putstr_fd("Invalid arguments\n", 2);
		*status = 1;
		return (*env);
	}
	if (!(new = get_env(*env, 2)))
		if (!(new = (char**)ft_memalloc(sizeof(char*) * 2)))
			return (NULL);
	del_tabstr(env);
	env = NULL;
	while (new[i])
		i++;
	new[i] = var_app(name, value);
	return (new);
}

int			ft_setenv(char **tab, char ***env)
{
	int		pos;
	char	**save;
	int		status;

	status = 0;
	if (len_array(tab) == 1 || len_array(tab) > 3)
	{
		ft_putstr_fd("usage: setenv Name [Value]\n", 2);
		return (1);
	}
	pos = in_env(tab[1], *env);
	if (pos >= 0)
	{
		save = *env;
		while (pos--)
			(*env)++;
		ft_strdel(&(**env));
		**env = var_app(tab[1], tab[2]);
		*env = save;
	}
	else
		*env = env_app(tab[1], tab[2], env, &status);
	if (env == NULL)
		return (1);
	return (status);
}
