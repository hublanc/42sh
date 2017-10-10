/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_shellname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:53:21 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 11:55:00 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_ttyname(char **line, int *i)
{
	char	*name;
	char	*before;
	char	*after;

	name = ttyname(0);
	name = ft_strrchr(name, '/');
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	if (name[0] && name[0] == '/')
		name++;
	*i += ft_strlen(name);
	ft_strdel(line);
	*line = before_curr_after(&before, name, &after);
}

void	get_shell_name(char **line, int *i)
{
	char *before;
	char *after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, "42sh", &after);
}
