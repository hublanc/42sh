/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:30:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/11 17:37:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	add_escape(char	**line, int *i)
{
	char	tmp[2];
	char		*after;
	char		*before;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	tmp[1] = '\0';
	tmp[0] = '\e';
	ft_strdel(line);
	*line = before_curr_after(&before, tmp, &after);
}
