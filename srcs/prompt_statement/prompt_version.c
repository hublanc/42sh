/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_version.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:51:49 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 12:03:11 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_version(char **line, int *i, int mode)
{
	char	*before;
	char	*after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	if (mode == 1)
		*line = before_curr_after(&before, "1.0", &after);
	else
		*line = before_curr_after(&before, "1.0.0", &after);
}
