/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tputchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:14:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/09 14:10:26 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		tputchar(int c)
{
	write(1, &c, 1);
	return (c);
}

char	*get_path_str(void)
{
	int		fd;
	char	*s[2];
	char	*new;

	if ((fd = open("/etc/paths", O_RDONLY)) == -1)
		return (NULL);
	s[1] = NULL;
	if (!(s[0] = ft_strnew(0)))
		return (NULL);
	while (get_next_line(fd, &s[1]))
	{
		if (ft_strlen(s[0]))
			s[0] = ft_strapp(s[0], ":");
		s[0] = ft_strapp(s[0], s[1]);
		ft_strdel(&s[1]);
	}
	ft_strdel(&s[1]);
	new = ft_strdup("PATH=");
	new = ft_strapp(new, s[0]);
	ft_strdel(&s[0]);
	close(fd);
	return (new);
}
