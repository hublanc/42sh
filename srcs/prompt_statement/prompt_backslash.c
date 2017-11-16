/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:52:35 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 10:36:29 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_backslash(char **line, int *i)
{
	char	*before;
	char	*after;

	if (!line || !*line)
		return ;
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, "\\", &after);
}

void	del_backslash(char **line, int *i)
{
	char	*before;
	char	*after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 1, ft_strlen(*line) - *i - 1);
	ft_strdel(line);
	*line = before_curr_after(&before, "", &after);
}
