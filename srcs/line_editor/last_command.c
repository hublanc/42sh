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
	while (command[a])
	{
		if (command[a] == '\'' || command[a] == '"')
			modify_quotes(&sq, &dq, command[a]);
		else if ((command[a] == '!' || command[a] == '^') && sq == 0 && dq == 0)
			wd_designator_2(command, &a, &str, history);
		else
			str = ft_str_chr_cat(str, command[a]);
		a++;
	}
	ft_putstr("Result == ");
	ft_putendl(str);
	return (str);
}

void		wd_designator_2(char *command, int *index, char **str, t_control **history)
{
	if (command[*index + 1] && command[*index + 1] == '!'
		&& (!command[*index + 2] || (command[*index + 2]
			&& command[*index + 2] != ':')))
		get_d_bang(&command[*index], str, history, index);			//	!!
	else if (is_d_dot(&command[*index]))
		get_old_flags(&command[*index], str, history, index);		//	!old_command:args
	else if (command[*index + 1] && ft_isdigit(command[*index + 1]))
		get_n_first(&command[*index], str, history, index);			//	!n
	else if (command[*index + 1] && command[*index + 1] == '-')
		get_n_last(&command[*index], str, history, index);			//	!-n
	else if (command[*index + 1] && command[*index + 1] == '#')
		get_line_again(command, index, str, history);				//	!#
//	else if (command[*index + 1] && command[*index + 1] == '?')
		// test														//	!?string[?]
	else if (command[*index] == '^')
		get_last_sub(&command[*index], index, str, history);		//	^string1^string2^
	else
		get_last_command(&command[*index], str, history, index);	//	!command
}

void		get_n_last(char *command, char **str, t_control **history, int *index)
{
	int		a;
	int		b;
	t_lst	*tmp;

	a = 1;
	b = ft_atoi(&command[2]);
	tmp = NULL;
	if (*history && (*history)->begin)
		tmp = (*history)->begin;
	while (tmp != NULL && a < b)
	{
		tmp = tmp->next;
		a++;
	}
	if (tmp)
	{
		a = 0;
		while (tmp->name[a])
		{
			(*str) = ft_str_chr_cat(*str, tmp->name[a]);
			a++;
		}
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;	
}

void		get_n_first(char *command, char **str, t_control **history, int *index)
{
	int		a;
	int		b;
	t_lst	*tmp;

	a = 1;
	b = ft_atoi(&command[1]);
	tmp = NULL;
	if (*history && (*history)->end)
		tmp = (*history)->end;
	while (tmp != NULL && a < b)
	{
		tmp = tmp->prev;
		a++;
	}
	if (tmp)
	{
		a = 0;
		while (tmp->name[a])
		{
			(*str) = ft_str_chr_cat(*str, tmp->name[a]);
			a++;
		}
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;
}

void		get_last_sub(char *command, int *index, char **str, t_control **history)
{		// ^string1^string2^
	char	**tmp;
	int		a;
	int		b;

	tmp = NULL;
	if (!check_sub_synt(command))
	{
		set_error(2, command);
		return;
	}
	tmp = split_spec(command);
	ft_putchar('a');
	if (!(ft_strstr((*history)->begin->name, tmp[0])))
	{
		ft_putchar('b');
		set_error(2, command);
		return;
	}
	ft_putchar('c');
	a = 0;
	while (command[a] && command[a] != ' ')
	{
		ft_putchar('d');
		if (ft_strncmp(&command[a], tmp[0], ft_strlen(tmp[0])) == 0)
			break;
		(*str) = ft_str_chr_cat(*str, command[a]);
		a++;
	}
	ft_putchar('e');
	b = 0;
	while (tmp[1][b])
	{
		(*str) = ft_str_chr_cat(*str, tmp[1][b]);
		b++;
	}
	b = 0;
	while (b <= (int)ft_strlen(tmp[0]) && command[a])
	{
		a++;
		b++;
	}
	while (command[a])
	{
		(*str) = ft_str_chr_cat(*str, command[a]);
		a++;
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;
	ft_strdel(&tmp[0]);
	ft_strdel(&tmp[1]);
	free(tmp);
}

char		**split_spec(char *command)
{
	char	**result;
	int		a;
	int		size;

	if (!(result = (char **)malloc(sizeof(char *) * (3))))
		exit(EXIT_FAILURE);
	if (!(result[0] = (char *)malloc(sizeof(char) * 1)))
		exit(EXIT_FAILURE);
	if (!(result[1] = (char *)malloc(sizeof(char) * 1)))
		exit(EXIT_FAILURE);
	result[0][0] = '\0';
	result[1][0] = '\0';
	a = 0;
	size = 1;
	while (command[size])
	{
		if (command[size] == '^')
		{
			a++;
		}
		else
		{
			result[a] = ft_str_chr_cat(result[a], command[size]);
		}
		size++;
	}
	result[2] = NULL;
	return (result);
}

int			check_sub_synt(char *command)
{
	int		a;
	int		b;
	int		c;

	a = 0;
	b = 0;
	c = 1;
	while (command[a] && command[a] != ' ')
	{
		if (command[a] == '^')
		{
			b++;
			if (c == 0)
				return (0);
			c = 0;
		}
		else
			c++;
		a++;
	}
	if (b != 3)
		return (0);
	return (1);
}

void		get_line_again(char *command, int *index, char **str, t_control **history)
{		// !#
	int		a;

	a = 0;
	while (a != *index)
	{
		(*str) = ft_str_chr_cat(*str, command[a]);
		a++;
	}
	(void)history;
	while (command[*index] && command[*index] != ' ')
		(*index)++;
}

void		get_last_command(char *command, char **str, t_control **history, int *index)
{		// !command
	int		a;
	char	*tmp;
	t_lst	*lst;

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
	lst = (*history)->begin;
	while (lst != NULL)
	{
		if (ft_strncmp(tmp, lst->name, ft_strlen(tmp)) == 0)
		{
			ft_putstr("Found == ");
			ft_putendl(lst->name);
			break;
		}
		lst = lst->next;
	}
	if (lst != NULL)
	{
		a = 0;
		ft_putchar('a');
		while (lst->name[a])
		{
			*str = ft_str_chr_cat(*str, lst->name[a]);
			a++;
		}		
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;
	ft_strdel(&tmp);
}

void		set_error(int a, char *command)
{
	int		b;

	b = 0;
	if (a == 1)
		ft_putendl("shell: syntax error near unexpected token `newline'");
	else if (a == 2)
	{	
		ft_putstr("shell : s:");
		while (command[b] && command[b] != ' ')
		{
			ft_putchar(command[b]);
			b++;
		}
		ft_putendl(": substitution failed");
	}
}

void		get_old_flags(char *command, char **str, t_control **history, int *index)
{		// !old_command:args
	int		a;
	size_t	size;
	char	*tmp;
	t_lst	*lst;

	a = 0;
	size = 0;
	while (command[size] && command[size] != ':')
		size++;
	if (!(tmp = (char *)malloc(sizeof(char) * (size + 1))))
		exit(EXIT_FAILURE);
	size = 0;
	while (command[size] && command[size] != ':')
	{
		tmp[size] = command[size];
		size++;
	}
	tmp[size] = '\0';
	lst = (*history)->begin;
	while (lst != NULL)
	{
		if (ft_strncmp(tmp, lst->name, ft_strlen(tmp)))
			break;
		lst = lst->next;
	}
	if (lst)
	{
		size = 0;
		while (lst->name[size] && lst->name[size] != ' ')
			size++;
		// set as many as args as need
	}
	(void)str;
	while (command[*index] && command[*index] != ' ')
		(*index)++;
	ft_strdel(&tmp);
}

void		get_d_bang(char *command, char **str, t_control **history, int *index)
{		// !!
	int		a;

	a = 0;
	if (!((*history)->begin->name))
		return ;
	while ((*history)->begin->name[a])
	{
		*str = ft_str_chr_cat(*str, (*history)->begin->name[a]);
		a++;
	}
	while (command[*index] && command[*index] != ' ')
		(*index)++;
}

void		modify_quotes(int *sq, int *dq, char c)
{
	if (c == '\'')
	{
		if (*sq >= 1)
			(*sq)--;
		else if (*sq == 0)
			(*sq)++;
	}
	else if (c == '"')
	{
		if (*dq >= 1)
			(*dq)--;
		else if (*dq == 0)
			(*dq)++;
	}
}

int			is_d_dot(char *str)
{
	int		a;

	a = 0;
	while (str[a] && str[a] != ' ')
	{
		if (str[a] == ':')
			return (1);
		a++;
	}
	return (0);
}
/*
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
*/
/*
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
*/

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
