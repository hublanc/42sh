/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:48:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 10:29:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_path(char ***env)
{
	int		i;

	if (!env || !*env || !**env)
		return (NULL);
	i = -1;
	while ((*env)[++i])
		if (!ft_strncmp("PATH=", (*env)[i], 5))
			return ((*env)[i]);
	return (NULL);
}

DIR			*check_open(char **path)
{
	DIR		*dirp;
	int		i;

	if (!path || !path[0])
		return (NULL);
	if (!(dirp = opendir(*path)))
	{
		i = ft_strlen(*path) - 1;
		while (i > 0 && (*path)[i] && (*path)[i] != '/')
			i--;
		ft_bzero((*path + i), ft_strlen(*path + i));
		if (!*path || !(dirp = opendir(*path)))
		{
			if (*path)
				free(*path);
			return (NULL);
		}
	}
	return (dirp);
}

static void	compl_cmp(t_compl *compl, char **word)
{
	int	i;

	if (!word || !word[0])
		return ;
	if ((*word)[0] == '.' && (!(*word)[1] || ((*word)[1] != '.'
					&& (*word)[1] != '/' && !(*word)[2])))
		compl->isdot = 1;
	if (compl->isdot || (*word)[ft_strlen(*word) - 1] == '/')
		compl->isslash = 1;
	compl->isstar = (compl->isstar == 3) ? 2 : 0;
	i = ft_strlen(*word) - 1;
	while (i > 0 && (*word)[i] != '/')
		i--;
	if ((*word)[i] == '/')
		i++;
	if (!(*word)[i] || (!compl->isdot && i <= 0))
	{
		free(*word);
		*word = NULL;
	}
	else if (!compl->isdot && i > 0 && (compl->isslash = 1) > 0)
	{
		ft_memmove(*word, (*word + i), ft_strlen((*word + i)));
		ft_bzero((*word + ft_strlen((*word + i))), ft_strlen((*word + i)));
	}
}

void		list_content(t_compl *compl)
{
	DIR			*dirp;
//	t_coargs	*args;

	if (!(dirp = check_open(&compl->path)))
		return ;
	compl_cmp(compl, &compl->arg);
//	if (compl_cmp(c, compl->path, &compl->arg) || ft_strcmp(compl->path, ".") == 0)
}

void		list_compl(t_compl *compl, char ***env)
{
	char	*path;
	char	**paths;

	paths = NULL;
	compl->args.next = NULL;
	compl->args.arg = NULL;
	compl->maxlen = 0;
	compl->nbrargs = 0;
	compl->isstar = 0;
	compl->isdot = 0;
	compl->isslash = 0;
	if (compl->arg && compl->arg[0] && ft_strcmp(compl->arg, "*") == 0)
		compl->isstar = 1;
	if (compl->arg && compl->arg[0] && ft_strcmp(compl->arg, "*") == 0)
		ft_bzero(compl->arg, ft_strlen(compl->arg));
	else if (compl->arg && compl->arg[0] && compl->arg[ft_strlen(compl->arg) - 1] == '*')
		compl->isstar = 3;
	if (compl->isstar == 3)
		compl->arg[ft_strlen(compl->arg) - 1] = 0;
	list_content(compl);
	if ((path = get_path(env)))
		paths = ft_strsplit(path + 5, ':');
	if (paths && paths[0])
		get_args(compl, paths);
}
