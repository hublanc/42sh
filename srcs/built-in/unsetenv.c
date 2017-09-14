/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:47:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/07/24 12:10:58 by hublanc          ###   ########.fr       */
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
	if (!(new = (char**)ft_memalloc(sizeof(char*) * len)))
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

void		ft_unsetenv(char **tab, char ***env)
{
	int			pos;
	char		**new;
	int			i;

	if (len_array(tab) < 2)
		return (ft_putstr_fd("usage: unsetenv Key\n", 2));
	i = 1;
	while (tab && tab[i])
	{
		pos = in_env(tab[i], *env);
		if (pos != -1)
		{
			new = delonenv(tab[i], *env);
			del_tabstr(env);
			*env = new;
		}
		else
		{
			ft_putstr_fd(tab[i], 2);
			ft_putstr_fd(" not found\n", 2);
		}
		i++;
	}
}
