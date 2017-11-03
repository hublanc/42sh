/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:52:19 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/03 21:01:22 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**designator_fnc(char **hist_line, t_bang2 *bang)
{
	int		begin;
	int		end;

	begin = 0;
	end = 0;
	if (!hist_line)
		return (NULL);
	find_begin(bang, &begin, &end, hist_line);
	find_end(bang, &begin, &end, hist_line);
	if (end < begin && bang->dash)
		return (return_error_bad_wspec(bang, hist_line));
	else
		return (dup_free_return(hist_line, begin, end));
}

void		find_begin(t_bang2 *bang, int *begin, int *end, char **hist_line)
{
	if (bang->x)
		*begin = bang->x;
	else if (bang->x == 0 && bang->c_x == '$')
		*begin = tablen(hist_line) - 1;
	else if (bang->x == 0 && bang->c_x == '^')
		*begin = 1;
	else if (bang->x == 0 && bang->c_x == '*')
	{
		if (!(bang->y) && !(bang->c_y))
		{
			*begin = 1;
			*end = tablen(hist_line) - 1;
		}
	}
}

void		find_end(t_bang2 *bang, int *begin, int *end, char **hist_line)
{
	if (bang->dash)
	{
		if (bang->y)
			*end = bang->y;
		else if (bang->y == 0 && bang->c_y == 0 && bang->dash)
			*end = tablen(hist_line) - 2;
	}
	if (bang->y == 0 && bang->c_y == '$')
		*end = tablen(hist_line) - 1;
	else if (bang->y == 0 && bang->c_y == '^')
		*end = 1;
	else if (bang->y == 0 && bang->c_y == '*')
		*end = tablen(hist_line) - 1;
	if (*end == 0)
		*end = *begin;
}

char		**dup_free_return(char **hist_line, int begin, int end)
{
	int		i;
	char	**result;

	if (!(result = (char **)malloc(sizeof(char *) * (end - begin + 2))))
		return (NULL);
	i = 0;
	while (hist_line[begin + i] && (begin + i) <= end)
	{
		result[i] = ft_strdup(hist_line[begin + i]);
		i++;
	}
	result[i] = NULL;
	i = 0;
	while (hist_line[i])
	{
		ft_strdel(&hist_line[i]);
		i++;
	}
	free(hist_line);
	return (result);
}

char		**return_error_bad_wspec(t_bang2 *bang, char **hist_line)
{
	int		i;

	i = 0;
	while (hist_line[i])
	{
		ft_strdel(&hist_line[i]);
		i++;
	}
	free(hist_line);
	ft_putstr_fd("shell: ", 2);
	if (bang->x)
		ft_putnbr_fd(bang->x, 2);
	else if (bang->c_x)
		ft_putchar_fd(bang->c_x, 1);
	ft_putchar_fd('-', 2);
	if (bang->y)
		ft_putnbr_fd(bang->y, 2);
	else if (bang->c_y)
		ft_putchar_fd(bang->c_y, 2);
	ft_putendl_fd(": bad word specifier", 2);
	return (NULL);
}
