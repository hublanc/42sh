/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:55:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 10:19:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_pwd_prompt(void)
{
	char	*path;

	if (!(path = get_elem(save_env(NULL), "PWD=")) && get_loc("PWD"))
		path = get_loc("PWD")->value;
	if (!path)
	{
		path = ft_strnew(256);
		getcwd(path, 256);
	}
	else
		path = ft_strdup(path);
	return (path);
}

static void	clear_last_slash(char **path)
{
	char	*tmp;
	size_t	i;

	tmp = *path;
	i = ft_strlen(*path);
	while (i > 0 && tmp[i - 1] == '/' && ft_strcmp(tmp, "/"))
		i--;
	*path = ft_strsub(*path, 0, i);
	ft_strdel(&tmp);
}

void		prompt_path(char **line, int *i, int mode)
{
	char	*path;
	char	*final_path;
	char	*before;
	char	*after;

	path = get_pwd_prompt();
	clear_last_slash(&path);
	if (mode == 2 && path)
		final_path = ft_strrchr(path, '/');
	else
		final_path = ft_strdup(path);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	if (final_path && final_path[0]
			&& final_path[0] == '/' && final_path[1] && mode == 2)
		*line = before_curr_after(&before, final_path + 1, &after);
	else
		*line = before_curr_after(&before, final_path, &after);
	if (mode != 2)
		ft_strdel(&final_path);
	ft_strdel(&path);
}
