/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:44:34 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 18:53:00 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_hist			*load_history()
{
	int		fd;
	char	*str;
	t_hist	*history;

	history = NULL;
	str = NULL;
	fd = open(".shell_history",
			O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	while (get_next_line(fd, &str))
	{
		if (str)
			add_begin(&history, new_history(str));
		ft_strdel(&str);
	}
	if (str)
		ft_strdel(&str);
	close(fd);
	return (history);
}

void			save_history(t_hist **history, char *str)
{
	int		fd;
	t_hist	*tmp;

	fd = open(".shell_history",
			O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putendl_fd(str, fd);
	add_begin(history, new_history(str));
	tmp = *history;
	while (tmp)
	{
		if (tmp->selected == 1)
			tmp->selected = 0;
		tmp = tmp->next;
	}
	close(fd);
}
