/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:55:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 12:03:35 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_path(char **line, int *i, int mode)
{
	char	path[256];
	char	*final_path;
	char	*before;
	char	*after;

	getcwd(path, 256);
	if (mode == 2)
		final_path = ft_strrchr(path, '/');
	else
		final_path = ft_strdup(path);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	if (final_path[0] && final_path[0] == '/')
		*line = before_curr_after(&before, final_path + 1, &after);
	else
		*line = before_curr_after(&before, final_path, &after);
	if (mode != 2)
		ft_strdel(&final_path);
}
