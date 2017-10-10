/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:48:36 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 13:45:44 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_time_prompt(char **line, int *i, int mode)
{
	char		*curr_time;
	time_t		t;
	struct tm	current;
	char		*before;
	char		*after;

	time(&t);
	current = *localtime(&t);
	current.tm_hour -= (mode != 1 && current.tm_hour > 12) ? 12 : 0;
	before = ft_itoa(current.tm_hour);
	curr_time = ft_strdup(before);
	curr_time = ft_strapp(curr_time, ":");
	ft_strdel(&before);
	before = ft_itoa(current.tm_min);
	curr_time = ft_strapp(curr_time, before);
	curr_time = ft_strapp(curr_time, ":");
	ft_strdel(&before);
	before = ft_itoa(current.tm_sec);
	curr_time = ft_strapp(curr_time, before);
	ft_strdel(&before);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, curr_time, &after);
	ft_strdel(&curr_time);
}

void	get_time_prompt2(char **line, int *i)
{
	char		*curr_time;
	time_t		t;
	struct tm	current;
	char		*before;
	char		*after;

	time(&t);
	current = *localtime(&t);
	current.tm_hour -= (current.tm_hour > 12) ? 12 : 0;
	before = ft_itoa(current.tm_hour);
	curr_time = ft_strdup(before);
	ft_strdel(&before);
	curr_time = ft_strapp(curr_time, ":");
	before = ft_itoa(current.tm_min);
	curr_time = ft_strapp(curr_time, before);
	ft_strdel(&before);
	if (current.tm_hour < 12)
		curr_time = ft_strapp(curr_time, " AM");
	else
		curr_time = ft_strapp(curr_time, " PM");
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, curr_time, &after);
	ft_strdel(&curr_time);
}
