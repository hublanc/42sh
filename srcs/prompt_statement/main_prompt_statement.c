/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 10:28:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/16 19:16:05 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			join_free_all(char **date, int do_itoa)
{
	char	*to_free;

	to_free = ft_itoa(do_itoa);
	*date = ft_strapp(*date, to_free);
	ft_strdel(&to_free);
}

static void		get_prompt2(char **line, int *i)
{
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'u')
		get_username(line, i);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'v')
		get_version(line, i, 1);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'V')
		get_version(line, i, 2);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'w')
		prompt_path(line, i, 1);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'W')
		prompt_path(line, i, 2);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == '$')
		get_uid_prompt(line, i);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1]
			&& ft_isdigit((*line)[*i + 1]))
		get_octal_value(line, i, &(*line)[*i + 1]);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == '\\')
		add_backslash(line, i);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'e')
		add_escape(line, i);
	else
		del_backslash(line, i);
}

static void		get_prompt(char **line, int *i)
{
	if ((*line)[*i + 1] == 'd')
		get_date_prompt(line, i);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'h')
		get_hostname_prompt(line, i, 1);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'H')
		get_hostname_prompt(line, i, 2);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'l')
		get_ttyname(line, i);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 's')
		get_shell_name(line, i);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 't')
		get_time_prompt(line, i, 1);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'T')
		get_time_prompt(line, i, 2);
	else if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == '@')
		get_time_prompt2(line, i);
	else
		get_prompt2(line, i);
}

void			prompt_management(char **line)
{
	int		i;
	char	tmp[2];

	i = 0;
	tmp[1] = '\0';
	while ((*line) && (*line)[i])
	{
		if ((*line)[i] == '\\')
			get_prompt(line, &i);
		if ((*line)[i])
			i++;
	}
}
