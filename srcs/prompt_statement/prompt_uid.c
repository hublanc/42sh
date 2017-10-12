/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_uid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:55:47 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/12 11:59:52 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_uid_prompt(char **line, int *i)
{
	uid_t	uid;
	char	*before;
	char	*after;

	uid = getuid();
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	if (uid == 0)
		*line = before_curr_after(&before, "#", &after);
	else
		*line = before_curr_after(&before, "$", &after);
}
