/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:40:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/17 11:21:43 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	do_export_sub(char ***env, t_loc *loc, char **tab, char *name)
{
	char	**tab2;

	ft_putendl("OK:");
	disp_tab(tab);
	if (!(tab2 = (char **)ft_memalloc(sizeof(char *) * 4)))
		return (1);
	tab2[0] = ft_strdup("setenv");
	tab2[1] = (tab && tab[0]) ? tab[0] : ft_strdup(name);
	tab2[2] = (tab && tab[1]) ? tab[1] : ft_strdup(loc->value);
	tab2[3] = 0;
	ft_setenv(tab2, env);
	suppr_loc(tab2[1]);
	(tab2[0]) ? free(tab2[0]) : 0;
	(tab2[1]) ? free(tab2[1]) : 0;
	(tab2[2]) ? free(tab2[2]) : 0;
	free(tab2);
	return (0);
}

static int	do_export(char *name, char ***env)
{
	t_loc	*loc;
	char	**tab;

	tab = NULL;
	if (ft_strchr(name, '='))
		if (!(tab = ft_strsplit(name, '=')))
			return (1);
	if (!(loc = (tab) ? get_loc(tab[0]) : get_loc(name))
			&& (!tab || !tab[0] || !tab[1]))
	{
		(tab && tab[1]) ? free(tab[1]) : 0;
		(tab && tab[2]) ? free(tab[2]) : 0;
		(tab) ? free(tab) : 0;
		return (1);
	}
	return (do_export_sub(env, loc, tab, name));
}

int			export(char **tab, char ***env)
{
	int		i;
	int		status;

	if (!tab || !tab[0] || (tab[0] && !tab[1]) || !env || !*env)
		return (0);
	i = 0;
	status = 1;
	while (tab[++i])
		status = do_export(tab[1], env);
	return (status);
}
