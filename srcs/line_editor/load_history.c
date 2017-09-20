/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:44:34 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:43:22 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_control		*load_history()
{
	int			fd;
	char		*str;
	t_control	*history;

	history = NULL;
	str = NULL;
	fd = open(".history", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	while (get_next_line(fd, &str))
	{
		if (str)
			history = dll_add_new_elem_frnt(history, str);
		ft_strdel(&str);
	}
	if (str)
		ft_strdel(&str);
	close(fd);
	return (history);
}

void			save_history(t_control **history, char *str)
{
	int		fd;
	t_lst	*tmp;

	fd = open(".history", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ft_putendl_fd(str, fd);
	*history = dll_add_new_elem_frnt(*history, str);
	tmp = (*history)->begin;
	while (tmp)
	{
		if (tmp->selected == 1)
			tmp->selected = 0;
		tmp = tmp->next;
	}
	close(fd);
}

/*
**	Comportement du built-in HISTORY de sh :
**	- Lors du lancement, l'historique contient tout le contenu du fichier .sh_history
**	- Lors du lancement d'une commande, cette commande est rajoutee a l'historique,
**		mais pas au fichier .sh_history
**	- Lors de la fermeture de sh, (ou lorsque la commande history -a est lancee), le
**		nouveau contenu de l'historique est rajoute au fichier .sh_history
*/
