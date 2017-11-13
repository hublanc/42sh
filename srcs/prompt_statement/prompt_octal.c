/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:50:36 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 12:47:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	get_octal_value2(char **line, int *i, int int_octal, int size)
{
	char	*before;
	char	*after;
	char	tmp[2];

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + size + 2, ft_strlen(*line) - *i - size + 2);
	ft_strdel(line);
	tmp[1] = '\0';
	tmp[0] = int_octal;
	if (int_octal >= 32 && int_octal <= 126)
		*line = before_curr_after(&before, tmp, &after);
	else
	{
		*line = before_curr_after(&before, NULL, &after);
		*i -= size;
	}
}

void		get_octal_value(char **line, int *i, char *code)
{
	int		int_octal;
	char	tmp[2];
	int		power;
	int		j;
	int		size;

	(void)line;
	j = 0;
	tmp[1] = '\0';
	power = -1;
	int_octal = 0;
	while (power < 2 && code[power + 1] && ft_isdigit(code[power + 1]))
		power++;
	size = power;
	while (power >= 0 && code[j])
	{
		tmp[0] = code[j];
		int_octal += ft_atoi(tmp) * ft_power(8, power);
		power--;
		j += 1;
	}
	get_octal_value2(line, i, int_octal, size);
}
