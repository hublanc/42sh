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

char		*wd_designator(char *command, t_control **history)
{
	int		a;
	int		sq;
	int		dq;
	char	*str;

	a = 0;
	sq = 0;
	dq = 0;
	str = NULL;
	if (!(str = (char *)malloc(sizeof(char) * 1)))
		exit(EXIT_FAILURE);
	ft_strclr(str);
	while (command[a])
	{
		if (command[a] == '\'' || command[a] == '"')
			modify_quotes(&sq, &dq, command[a]);
		else if ((command[a] == '!') && sq == 0 && dq == 0)
			wd_designator_2(command, &a, &str, history);
		else
			str = ft_str_chr_cat(str, command[a]);
		a++;
	}
	if (str[ft_strlen(str) - 1] == ' ')
		str[ft_strlen(str) - 1] = '\0';
	if (ft_strchr(command, '!') != 0)
		add_hist_or_not(history, str);
	return (str);
}

void		wd_designator_2(char *command, int *index, char **str,
			t_control **history)
{
	if (command[*index + 1] && command[*index + 1] == '!')
		get_d_bang(&command[*index], str, history, index);
	else if (command[*index + 1] && ft_isdigit(command[*index + 1]))
		get_n_first(&command[*index], str, history, index);
	else if (command[*index + 1] && command[*index + 1] == '-')
		get_n_last(&command[*index], str, history, index);
	else if (command[*index + 1] && command[*index + 1] == '#')
		get_line_again(command, index, str, history);
	else
		get_last_command(&command[*index], str, history, index);
}

void		get_last_command(char *command, char **str, t_control **history,
			int *index)
{
	int		a;
	char	*tmp;

	if (!command[1])
	{
		set_error(1, NULL);
		return ;
	}
	a = 1;
	tmp = NULL;
	while (command[a] && command[a] != ' ')
		a++;
	if (!(tmp = (char *)malloc(sizeof(char) * (a + 1))))
		exit(EXIT_FAILURE);
	a = 1;
	while (command[a] && command[a] != ' ')
	{
		tmp[a - 1] = command[a];
		a++;
	}
	tmp[a - 1] = '\0';
	get_last_command_2(tmp, history, str);
	while (command[*index] && command[*index] != ' ')
		(*index)++;
	ft_strdel(&tmp);
}

void		get_last_command_2(char *tmp, t_control **history, char **str)
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
	}
	*str = ft_str_chr_cat(*str, ' ');
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
