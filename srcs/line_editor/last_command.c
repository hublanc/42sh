/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:56:16 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/25 16:30:02 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			init_wd_des(char **str, char *command, int *a, int *sq)
{
	int		z;

	z = 0;
	*a = 0;
	*sq = 0;
	*str = NULL;
	if (!(ft_strchr(command, '!')))
	{
		*str = ft_strdup(command);
		return (0);
	}
	while (command[z] && command[z] != '!')
		z++;
	z++;
	if (command[z] && command[z] != '-' && !ft_isdigit(command[z])
			&& command[z] != '!' && (!(command[z] >= 'a' && command[z] <= 'z')))
	{
		if (!(*str = ft_strdup(command)))
			return (-1);
		return (0);
	}
	if (!(*str = ft_memalloc(1)))
		return (-1);
	return (1);
}

char		*wd_designator(char *command, t_control **history)
{
	int		a;
	int		sq;
	int		dq;
	char	*str;

	dq = 0;
	if (!init_wd_des(&str, command, &a, &sq))
		return (str);
	while (a <= (int)ft_strlen(command) && command[a])
	{
		if (command[a] == '\'' || command[a] == '"')
			modify_quotes(&sq, &dq, command[a]);
		if ((command[a] == '!' && command[a + 1] && command[a + 1] != ' '
					&& sq == 0 && dq == 0)
				&& !wd_designator_2(command, &a, &str, history))
			return (NULL);
		else if (command[a])
			str = ft_str_chr_cat(str, command[a]);
		a++;
	}
	if (str[ft_strlen(str) - 1] == ' ')
		str[ft_strlen(str) - 1] = '\0';
	add_hist_or_not(history, str);
	ft_putstr("Returning ");
	ft_putendl(str);
	return (str);
}

int			wd_designator_2(char *command, int *index, char **str,
			t_control **history)
{
	if (*index - 1 >= 0 && command[*index - 1] && command[*index - 1] == '\\')
		*str = ft_str_chr_cat(*str, '!');
	else if (command[*index + 1] && command[*index + 1] == '!')
		get_d_bang(&command[*index], str, history, index);
	else if (command[*index + 1] && ft_isdigit(command[*index + 1]))
	{
		if (!get_n_first(&command[*index], str, history, index))
		{
			event_not_found(command);
			return (0);
		}
	}
	else if (command[*index + 1] && command[*index + 1] == '-')
	{
		if (!get_n_last(&command[*index], str, history, index))
		{
			event_not_found(command);
			return (0);
		}
	}
	else
		get_last_command(&command[*index], str, history, index);
	return (1);
}

int			get_last_command(char *command, char **str, t_control **history,
			int *index)
{
	int		a;
	char	*tmp;

	if (!command[1])
	{
		set_error(1, NULL);
		return (-1);
	}
	a = 1;
	tmp = NULL;
	while (command[a] && command[a] != ' ')
		a++;
	if (!(tmp = ft_memalloc(a + 1)))
		return (0);
	a = 1;
	while (command[a] && command[a] != ' ')
	{
		tmp[a - 1] = command[a];
		a++;
	}
	if (!get_last_command_2(tmp, history, str))
		return (0);
	a = 0;
	while (command[a] && command[a] != ' ')
		a++;
	(*index) += a;
	ft_strdel(&tmp);
	return (1);
}

int			get_last_command_2(char *tmp, t_control **history, char **str)
{
	t_lst	*lst;
	int		a;

	lst = NULL;
	if ((*history)->begin)
		lst = (*history)->begin;
	while (lst != NULL)
	{
		if (ft_strncmp(tmp, lst->name, ft_strlen(tmp)) == 0)
			break ;
		lst = lst->next;
	}
	if (lst != NULL)
	{
		a = 0;
		while (lst->name[a])
		{
			*str = ft_str_chr_cat(*str, lst->name[a]);
			a++;
		}
		*str = ft_str_chr_cat(*str, ' ');
		return (1);
	}
	return (0);
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
