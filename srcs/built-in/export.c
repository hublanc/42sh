/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:40:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/05 21:32:59 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int    do_export_sub(char ***env, t_loc *loc, char ***tab, char *name)
{
	char    **tab2;

	if (!(tab2 = (char **)ft_memalloc(sizeof(char *) * 4)))
	{
		del_tabstr(tab);
		return (1);
	}
	tab2[0] = ft_strdup("setenv");
	tab2[1] = (*tab && (*tab)[0]) ? ft_strdup((*tab)[0]) : ft_strdup(name);
	if ((*tab && (*tab)[0] && !(*tab)[1]) && (!loc || !loc->value))
		tab2[2] = NULL;
	else
		tab2[2] = (*tab && (*tab)[0] && (*tab)[1]) ?
			ft_strdup((*tab)[1]) : ft_strdup(loc->value);
	tab2[3] = NULL;
	ft_setenv(tab2, env);
	suppr_loc(tab2[1]);
	tab2 ? del_tabstr(&tab2) : 0;
	tab ? del_tabstr(tab) : 0;
	return (0);
}

static int	do_export(char *name, char ***env)
{
	t_loc	*loc;
	char	**tab;
	int		i;

	i = -1;
	while (name && (name[++i] == ' ' || name[i] == '='))
		if (name[i] == '=')
		{
			ft_putstr_fd(name, 2);
			ft_putstr_fd(" not a valid identifier\n", 2);
			return (0);
		}
	if (!(tab = NULL) && ft_strchr(name, '=') &&
			!(tab = ft_strsplit(name, '=')))
		return (1);
	if (!(loc = (tab) ? get_loc(tab[0]) : get_loc(name))
			&& (!tab || !tab[0]))
	{
		tab ? del_tabstr(&tab) : 0;
		return (1);
	}
	do_export_sub(env, loc, &tab, name);
	return (0);
}

static void	exported_display(char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		ft_putstr("export ");
		ft_putstr(env[i]);
		ft_putstr("\n");
		i++;
	}
}

static int	export_parse(char **tab, char *opt)
{
	int		j;
	int		i;

	i = 0;
	while (tab[++i] && tab[i][0] == '-')
	{
		j = 0;
		while (tab[i][++j])
		{
			if (tab[i][j] == 'p')
				*opt = 'p';
			else if (tab[i][j] != 'p')
			{
				ft_putstr_fd("shell: export: -", 2);
				ft_putchar_fd(tab[i][j], 2);
				ft_putstr_fd("\nexport name[=word] or export -p\n", 2);
				return (-1);
			}
		}
	}
	return (i);
}

int			export(char **tab, char ***env)
{
	char	opt;
	int		i;
	int		status;

	opt = 0;
	if (!tab || !tab[0] || !env || !*env)
		return (0);
	if ((i = export_parse(tab, &opt)) == -1)
		return (1);
	if ((opt == 'p' && !tab[i]) || !tab[1])
		exported_display(*env);
	status = 1;
	while (tab[i])
		status = do_export(tab[i++], env);
	return (status);
}
