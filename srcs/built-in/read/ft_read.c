/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:08:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/01 15:14:44 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**prep_setenv(char *name, char *value)
{
	char	**tab;

	if (!(tab = (char**)ft_memalloc(sizeof(char*) * 4)))
		return (NULL);
	tab[0] = ft_strdup("setenv");
	if (name)
		tab[1] = ft_strdup(name);
	if (value)
		tab[2] = ft_strdup(value);
	tab[3] = NULL;
	return (tab);
}

static int	read_put_in_var(char **cmd, char *readding)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	if (!valid_local_var(&cmd[g_optind]))
		return (1);
	if (readding && !(split = ft_strsplit(readding, ' ')))
		return (1);
	else if (!readding)
		return (0);
	tmp = ft_strnew(0);
	ft_putchar('\n');
	while (cmd[g_optind + 1])
		add_loc(cmd[g_optind++], split[i++]);
	while (split[i])
	{
		tmp = ft_strapp(tmp, split[i]);
		tmp = (split[i + 1]) ? ft_strapp(tmp, " ") : tmp;
		i++;
	}
	add_loc(cmd[g_optind], tmp);
	ft_strdel(&tmp);
	del_tabstr(&split);
	return (0);
}

static char	**default_mod(void)
{
	char	**new_cmd;

	if (!(new_cmd = (char**)ft_memalloc(sizeof(char*) * 2)))
		exit(EXIT_FAILURE);
	new_cmd[0] = ft_strdup("REPLY");
	new_cmd[1] = NULL;
	return (new_cmd);
}

int		ft_read(char **cmd)
{
	int		opt;
	int		default_read;
	char	*readding;
	int		error;

	read_singleton(1);
	default_read = 0;
	readding = NULL;
	g_optind = 0;
	opt = get_read_opt(cmd);
	if (cmd && !cmd[g_optind])
	{
		default_read = 1;
		cmd = default_mod();
	}
	if (opt != 0 && opt != 'r')
		return (2);
	readding = (opt == 'r') ? read_r_opt() : read_without_opt();
	error = read_put_in_var(cmd, readding);
	if (default_read)
		del_tabstr(&cmd);
	ft_strdel(&readding);
	if (error)
		return (error);
	return (0);
}
