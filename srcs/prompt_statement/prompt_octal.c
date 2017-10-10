/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:50:36 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 12:04:59 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	get_octal_value2(char **line, int *i, char **octal)
{
	char	*before;
	char	*after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 4, ft_strlen(*line) - *i - 4);
	ft_strdel(line);
	*i += ft_strlen(*octal);
	*line = before_curr_after(&before, *octal, &after);
	ft_strdel(octal);
}

void		get_octal_value(char **line, int *i, char *code)
{
	char	*octal;
	char	tmp[2];
	int		int_octal;
	int		curs;
	int		j;

	int_octal = 0;
	octal = NULL;
	tmp[1] = '\0';
	curs = 0;
	j = 2;
	if (code[0] && code[1] && code[2] && ft_isdigit(code[0]) &&
			ft_isdigit(code[1]) && ft_isdigit(code[2]))
	{
		while (curs < 3)
		{
			tmp[0] = code[curs];
			int_octal += ft_atoi(tmp) * ft_power(8, j);
			j--;
			curs++;
		}
		octal = ft_itoa(int_octal);
	}
	get_octal_value2(line, i, &octal);
}
