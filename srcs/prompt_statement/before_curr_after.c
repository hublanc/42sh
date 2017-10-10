/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_curr_after.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:44:35 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 13:10:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*before_curr_after(char **before, char *curr, char **after)
{
	char	*line;

	line = ft_strnew(0);
	if (*before)
		line = ft_strapp(line, *before);
	line = ft_strapp(line, curr);
	if (*after)
		line = ft_strapp(line, *after);
	ft_strdel(before);
	ft_strdel(after);
	return (line);
}
