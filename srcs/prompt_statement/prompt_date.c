/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_date.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:46:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/16 19:15:02 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*return_date(void)
{
	struct tm	current;
	char		*date;
	static char	*day_array[7] =
	{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	static char	*month_array[12] = {" Jan ", " Feb ", " Mar ", " Apr ", " May ",
		" Jun ", " Jul ", " Aug ", " Sep ", " Oct ", " Nov ", " Dec "};
	time_t		t;

	time(&t);
	current = *localtime(&t);
	date = ft_strdup(day_array[current.tm_wday]);
	date = ft_strapp(date, month_array[current.tm_mon]);
	join_free_all(&date, current.tm_mday);
	return (date);
}

void		get_date_prompt(char **line, int *i)
{
	char		*date;
	char		*after;
	char		*before;

	date = return_date();
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	*i += ft_strlen(date) - 1;
	ft_strdel(line);
	*line = before_curr_after(&before, date, &after);
	ft_strdel(&date);
}
