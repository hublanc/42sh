/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 10:48:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/27 11:45:22 by amazurie         ###   ########.fr       */
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

DIR			*check_open(t_compl *compl)
{
	DIR		*dirp;
	int		i;

	if (!(dirp = opendir(compl->path)))
	{
		i = ft_strlen(compl->path) - 1;
		while (i > 0 && compl->path[i] && compl->path[i] != '/')
			i--;
		i++;
		ft_bzero(compl->path + i, ft_strlen(compl->path + i));
		if (!compl->path || !(dirp = opendir(compl->path)))
		{
			if (compl->path)
				free(compl->path);
			compl->path = NULL;
			if ((dirp = opendir(".")))
			{
				compl->bi = 0;
				compl->isslash = 1;
				return (dirp);
			}
			return (NULL);
		}
	}
	return (dirp);
}

static void	compl_cmp(t_compl *compl, char **word)
{
	int	i;

	if (!word || !*word || !(*word)[0] || !compl->path
			|| ft_strncmp(compl->path, *word, ft_strlen(compl->path))
			|| (*word)[0] != compl->path[0])
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
	t_coargs	*args;
	int			id;

	compl->maxlen = 0;
	compl->nbrargs = 0;
	compl->isdot = 0;
	compl->isslash = 0;
	if (!(dirp = check_open(compl)))
		return ;
	compl_cmp(compl, &compl->arg);
	if (compl->arg && compl->arg[0] == '.')
		compl->isdot = 1;
	if (compl->arg && !ft_strcmp(compl->arg, "*"))
	{
		free(compl->arg);
		compl->arg = NULL;
	}
	args = &compl->args;
	id = 0;
	get_files(compl, dirp, &args, &id);
	closedir(dirp);
}

static int	check_command(t_cmd *cmd)
{
	int		i;

	if (!cmd->str || !cmd->str[0])
		return (0);
	i = cmd->col - 2 - cmd->prlen;
	if (i <= 0)
		return (0);
	while (cmd->str[i] && cmd->str[i] != 32 && cmd->str[i] != 34
				&& cmd->str[i] != 96)
		i--;
	if (i <= 0)
		return (0);
	while (cmd->str[i] && (cmd->str[i] == 32 || cmd->str[i] == 34
				|| cmd->str[i] == 96))
		i--;
	if (cmd->str[i] == 32)
		return (0);
	return (1);
}

void		list_compl(t_compl *compl, t_cmd *cmd, char ***env)
{
	t_coargs	*ar;
	char		*path;
	char		**paths;

	paths = NULL;
	compl->args.next = NULL;
	compl->args.arg = NULL;
	compl->isstar = 0;
	compl->bi = 1;
	if (compl->arg && compl->arg[0] && !ft_strcmp(compl->arg, "*"))
		compl->isstar = 1;
	if (compl->arg && compl->arg[0] && !ft_strcmp(compl->arg, "*"))
	{
		free(compl->path);
		compl->path = ft_strdup(".");
	}
	else if (compl->arg && compl->arg[0] && compl->arg[ft_strlen(compl->arg) - 1] == '*')
		compl->isstar = 3;
	if (compl->isstar == 3)
		compl->arg[ft_strlen(compl->arg) - 1] = 0;
	list_content(compl);
	if (!check_command(cmd) && !compl->isstar && !compl->bi
			&& (path = get_path(env)))
		if ((paths = ft_strsplit(path + 5, ':')) && paths[0])
			get_args(compl, paths);
	ar = &compl->args;
	while (ar && ar->next && ar->next->arg)
		ar = ar->next;
	(ar && ar->next && !ar->next->arg) ? free(ar->next) : 0;
	ar->next = NULL;
}
