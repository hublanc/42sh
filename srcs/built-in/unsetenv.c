/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:47:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/01 15:08:05 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**delonenv(char *name, char **env)
{
	char		**new;
	char		*dup;
	int			len;
	int			i;

	len = 0;
	i = 0;
	if (!env || !*env)
		return (NULL);
	if (!name)
		return (env);
	while (env[len])
		len++;
	if (!(new = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (*env)
	{
		dup = ft_strsub(*env, 0, ft_strchr(*env, '=') - *env);
		if (ft_strcmp(dup, name) != 0)
			new[i++] = ft_strdup(*env);
		env++;
		ft_strdel(&dup);
	}
	return (new);
}

static int	sub_unsetenv(char **tab, char ***env)
{
	int			i;
	int			pos;
	int			status;
	char		**new;

	i = 1;
	while (tab && tab[i])
	{
		pos = in_env(tab[i], *env);
		if (pos != -1)
		{
			new = delonenv(tab[i], *env);
			del_tabstr(env);
			*env = new;
			status = 0;
		}
		else
		{
			ft_putstr_fd(tab[i], 2);
			ft_putstr_fd(" not found\n", 2);
			status = 1;
		}
		i++;
	}
	return (status);
}

int			ft_unsetenv(char **tab, char ***env)
{
	if (len_array(tab) < 2)
		return (print_error(7, NULL));
	return (sub_unsetenv(tab, env));
}
