/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:44:34 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/10 19:44:52 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_control		*load_history(char **env)
{
	int			fd;
	char		*str;
	t_control	*history;
	char		*file;

	history = NULL;
	str = NULL;
	if ((file = get_history_file(&env)) == NULL)
		return (NULL);
	if (access(file, F_OK) != 0 || access(file, R_OK | W_OK) != 0)
		return (NULL);
	fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (NULL);
	free(file);
	while (get_next_line(fd, &str) > 0)
	{
		if (str)
			history = dll_add_new_elem_frnt(history, str);
		ft_strdel(&str);
	}
	close(fd);
	if (history)
		history->original_length = history->length;
	return (history);
}

int				get_history_file_size(char *file_name)
{
	int		fd;
	char	*str;
	int		size;

	fd = open(file_name,
			O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	size = 0;
	if (fd == -1)
		return (size);
	while (get_next_line(fd, &str))
	{
		size++;
		ft_strdel(&str);
	}
	close(fd);
	return (size);
}

int				save_history_in_file(t_control **history, char *file_name)
{
	int		file_size;
	t_lst	*tmp;
	int		fd;

	file_size = get_history_file_size(file_name) - 1;
	if ((*history)->length == file_size)
		return (0);
	tmp = (*history)->end;
	while (file_size >= 0 && tmp != NULL)
	{
		file_size--;
		tmp = tmp->prev;
	}
	fd = open(file_name,
		O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->name, fd);
		tmp = tmp->prev;
	}
	close(fd);
	return (0);
}

int				save_history(t_control **history, char *str, char *file)
{
	int		fd;
	t_lst	*tmp;

	fd = open(file,
		O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (-1);
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
	return (0);
}

/*
**	Comportement du built-in HISTORY de sh :
**	- Lors du lancement, l'historique contient tout le contenu du fichier
**		.sh_history
**	- Lors du lancement d'une commande, cette commande est rajoutee a
**		l'historique, mais pas au fichier .sh_history
**	- Lors de la fermeture de sh, (ou lorsque la commande history -a est
**		lancee), le nouveau contenu de l'historique est rajoute au fichier
**		.sh_history
*/
