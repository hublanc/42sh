/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_username.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:49:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 12:02:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_username(char **line, int *i)
{
	char	*username;
	char	*before;
	char	*after;

	if (!(username = ft_memalloc(sizeof(char) * 257)))
		exit(EXIT_FAILURE);
	getlogin_r(username, 256);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, username, &after);
	ft_strdel(&username);
}
