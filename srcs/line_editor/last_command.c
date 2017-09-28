/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:56:16 by mameyer           #+#    #+#             */
/*   Updated: 2017/09/26 13:56:17 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*last_command(char *command, t_control **history)
{
	char	*new;
	int		i;
	size_t	size;
	char	*tmp;

	new = NULL;
	i = 0;
	tmp = NULL;
	while (command[i] && i <= (int)ft_strlen(command))
	{
		if (command[i] == '!' && command[i + 1] && command[i + 1] == '!'
			&& history && (*history)->begin && (*history)->begin->name)
		{
			tmp = ft_strdup((*history)->begin->name);
			size = 0;
			while (tmp && tmp[size] != '\0')
			{
				new = ft_str_chr_cat(new, tmp[size]);
				size++;
			}
			ft_strdel(&tmp);
			while (command[i] && command[i] != 32)
				i++;
		}
		else if (command[i] == '!' && command[i + 1] && command[i + 1] == '-')
		{
			if (command[i + 2])
				tmp = ft_strdup(get_n_last(ft_atoi(&command[i + 2]), history));
			if (!tmp)
			{
				event_not_found(command);
				return (NULL);
			}
			size = 0;
			while (tmp && tmp[size] != '\0')
			{
				new = ft_str_chr_cat(new, tmp[size]);
				size++;
			}
			ft_strdel(&tmp);
			while (command[i] && command[i] != 32)
				i++;
		}
		else if (command[i] == '!' && command[i + 1]
			&& ft_isdigit(command[i + 1]))
		{
			tmp = ft_strdup(get_n_first(ft_atoi(&command[i + 1]), history));
			if (!tmp)
			{
				event_not_found(command);
				return (NULL);
			}
			size = 0;
			while (tmp && tmp[size] != '\0')
			{
				new = ft_str_chr_cat(new, tmp[size]);
				size++;
			}
			ft_strdel(&tmp);
			while (command[i] && command[i] != 32)
				i++;
		}
		else if (command[i] == '!'
			&& (i == 0 || (command[i - 1] && command[i - 1] == ' '))
			&& command[i + 1] && command[i + 1] >= 65 && command[i + 1] <= 122)
		{
			tmp = ft_strdup(get_last(&command[i + 1], history));
			if (!tmp)
			{
				event_not_found(command);
				return (NULL);
			}
			size = 0;
			while (tmp && tmp[size] != '\0')
			{
				new = ft_str_chr_cat(new, tmp[size]);
				size++;
			}
			ft_strdel(&tmp);
			while (command[i] && command[i] != 32)
				i++;
		}
		else if (command[i])
		{
			if (command[i] != ' ' && command[i - 1] && command[i - 1] == ' ')
				new = ft_str_chr_cat(new, command[i - 1]);
			new = ft_str_chr_cat(new, command[i]);
		}
		i++;
	}
	new = ft_str_chr_cat(new, '\0');
	(*history) = dll_add_new_elem_frnt(*history, new);
	return (new);
}

char		*get_n_first(int a, t_control **history)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	if (history && (*history)->end)
		tmp = (*history)->end;
	while (i < a - 1 && tmp != NULL)
	{
		tmp = tmp->prev;
		i++;
	}
	if (tmp && tmp->name)
	{
		ft_putstr("Found == ");
		ft_putendl(tmp->name);
		return (tmp->name);
	}
	else
		return (NULL);
}

char		*get_n_last(int a, t_control **history)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = NULL;
	if (history && (*history)->begin)
		tmp = (*history)->begin;
	while (i < a - 1 && tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp && tmp->name)
		return (tmp->name);
	else
		return (NULL);
}

char		*get_last(char *command, t_control **history)
{
	t_lst	*tmp;
	size_t	size;

	tmp = NULL;
	size = 0;
	while (command[size] && command[size] != 32)
		size++;
	if (history && (*history)->begin && (*history)->begin->next)
		tmp = (*history)->begin;
	while (tmp != NULL)
	{
		if (ft_strncmp(command, tmp->name, size) == 0)
			return (tmp->name);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
**	-------------------
**	COMPORTEMENT DE '!'
**	-------------------
**
**	Comportement de !command : Ajoute a la commande les flags utilises lors du
**	dernier appel de cette commande.
**	Peut etre combine avec des opérateurs.
**	last_command() va renvoyer une chaine de caractere en remplacant les '!' par
**	la derniere commande correspondant.
**
**	!-n : Execute la n derniere commande de l'hist
**
**	!n : Execute la n premiere commande de l'hist
**
**	!! : Execute la derniere commande (Equivalent de UP)
*/
