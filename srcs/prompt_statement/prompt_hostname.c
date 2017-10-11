/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_hostname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:47:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/11 17:50:45 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_hostname_prompt(char **line, int *i, int mode)
{
	char	*hostname;
	char	**split;
	char	*after;
	char	*before;

	if (!(hostname = ft_memalloc(sizeof(char) * 256)))
		exit (EXIT_FAILURE);
	gethostname(hostname, 256);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	if (mode == 1)
	{
		split = ft_strsplit(hostname, '.');
		ft_strdel(&hostname);
		hostname = ft_strdup(split[0]);
		free_tabl(split);
	}
	*i += ft_strlen(hostname) - 1;
	ft_strdel(line);
	*line = before_curr_after(&before, hostname, &after);
	ft_strdel(&hostname);
}
