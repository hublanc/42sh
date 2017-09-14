/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:51:12 by hublanc           #+#    #+#             */
/*   Updated: 2017/02/02 15:28:12 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*str_realloc(char *src)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strnew(BUFF_SIZE + ft_strlen(src));
	tmp = ft_strcpy(tmp, src);
	ft_strdel(&src);
	return (tmp);
}

t_fd		*fdnew(int fd, char *rest)
{
	t_fd		*new;

	if (!(new = (t_fd*)malloc(sizeof(t_list))))
		return (NULL);
	new->fd = fd;
	new->rest = rest;
	new->next = NULL;
	return (new);
}

t_fd		*seekfd(int fd, t_fd **fdlst)
{
	t_fd		*tmp;
	t_fd		*prev;

	tmp = *fdlst;
	prev = NULL;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	if (!(tmp = fdnew(fd, NULL)))
		return (NULL);
	if (prev)
		prev->next = tmp;
	else
		*fdlst = tmp;
	return (tmp);
}

int			create_line(t_fd *cur, char **line, int fd)
{
	char	*buf;
	int		i;

	buf = (cur->rest) ? ft_strdup(cur->rest) : ft_strnew(0);
	buf = str_realloc(buf);
	while (!ft_strchr(buf, '\n'))
	{
		if (read(fd, (buf + ft_strlen(buf)), BUFF_SIZE) <= 0)
			break ;
		buf = str_realloc(buf);
	}
	i = (ft_strchr(buf, '\n')) ? ft_strchr(buf, '\n') - buf : -1;
	if (i < 0)
	{
		*line = ft_strdup(buf);
		ft_strdel(&buf);
		ft_strdel(&(cur->rest));
		return ((**line == '\0') ? 0 : 1);
	}
	*line = ft_strsub(buf, 0, i);
	ft_strdel(&(cur->rest));
	cur->rest = ft_strsub(buf, i + 1, ft_strlen(buf) - i);
	ft_strdel(&buf);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_fd		*fdlst;
	t_fd			*current;

	if (fd < 0 || !line || (read(fd, 0, 0) < 0))
		return (-1);
	current = seekfd(fd, &fdlst);
	return (create_line(current, line, fd));
}
