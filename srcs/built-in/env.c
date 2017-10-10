/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 19:21:36 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/09 14:33:22 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			check_opt(char **tab, int *i, char ***env, char **opt)
{
	char	**new;

	*opt = ft_strnew(0);
	while (tab[*i] && tab[*i][0] == '-')
	{
		if (ft_strcmp(tab[*i], "-i") == 0)
			*opt = ft_str_chr_cat(*opt, tab[*i][1]);
		else if (ft_strcmp(tab[*i], "-u") == 0)
		{
			if (in_env(tab[++(*i)], *env) != -1)
			{
				new = delonenv(tab[(*i)], *env);
				del_tabstr(env);
				*env = new;
			}
		}
		else if (tab[*i][1] != '\0')
		{
			print_usage(tab[*i][1]);
			return (0);
		}
		tab[*i] ? (*i)++ : 0;
	}
	return (1);
}

void		check_set(char **tab, int *i, char ***env)
{
	char	*name;
	char	*set[3];
	int		pos;

	pos = *i;
	while (pos--)
		tab++;
	while (*tab && ft_strchr(*tab, '='))
	{
		name = ft_strsub(*tab, 0, ft_strchr(*tab, '=') - *tab);
		set[0] = "setenv";
		set[1] = get_elem(env, name);
		set[2] = ft_strchr(*tab, '=') + 1;
		ft_setenv(set, env);
		ft_strdel(&name);
		tab++;
		(*i)++;
	}
}

char		*app_cmd(char **tab, int i)
{
	char	*new;

	new = ft_strnew(0);
	if (!tab[i])
		return (new);
	new = ft_strapp(new, tab[i++]);
	while (tab[i])
	{
		new = ft_str_chr_cat(new, ' ');
		new = ft_strapp(new, tab[i++]);
	}
	return (new);
}

int			ft_env(char **env, char **tab)
{
	int		i;
	char	**cp;
	char	*opt;
	char	*cmd;

	i = 1;
	if (len_array(tab) == 1)
		return (env_tab(env));
	cp = get_env(env, 1);
	if (!check_opt(tab, &i, &cp, &opt))
	{
		del_tabstr(&cp);
		ft_strdel(&opt);
		return (1);
	}
	if (ft_strchr(opt, 'i'))
		del_tabstr(&cp);
	check_set(tab, &i, &cp);
	cmd = app_cmd(tab, i);
	routine(cmd, &cp, NULL);
	ft_strdel(&cmd);
	ft_strdel(&opt);
	if (cp)
		del_tabstr(&cp);
	return (return_status());
}
