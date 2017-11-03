/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_splitted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:52:19 by mameyer           #+#    #+#             */
/*   Updated: 2017/11/03 15:52:23 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**designator_fnc(char **hist_line, t_bang2 *bang)
{
	char	**result;
	int		begin;
	int		end;
	int		i;

	begin = 0;
	end = 0;
	i = 0;
	while (hist_line[i])
	{
		ft_putstr(hist_line[i]);
		ft_putchar('\t');
		i++;
	}
	ft_putchar('\n');
	if (!hist_line)
		return (NULL);
	result = NULL;
	

	// GET FIRST WD - SET BEGIN
	if (bang->x)
		begin = bang->x;
	else if (bang->x == 0 && bang->c_x == '$')
		begin = tablen(hist_line) - 1;
	else if (bang->x == 0 && bang->c_x == '^')
		begin = 1;
	else if (bang->x == 0 && bang->c_x == '*')
	{
		if (!(bang->y) && !(bang->c_y))
		{
			begin = 1;
			end = tablen(hist_line) - 1;
		}
	}
	// END OF GET END


	// GET SECOND WD - SET END
	if (bang->dash)
	{
		if (bang->y)
			end = bang->y;
		else if (bang->y == 0 && bang->c_y == 0 && bang->dash)
			end = tablen(hist_line) - 2;
	}
	if (bang->y == 0 && bang->c_y == '$')
		end = tablen(hist_line) - 1;
	else if (bang->y == 0 && bang->c_y == '^')
		end = 1;
	else if (bang->y == 0 && bang->c_y == '*')
		end = tablen(hist_line) - 1;

	if (end == 0)
		end = begin;
	// END OF GET END

	if (end < begin && bang->dash)
	{
		ft_putstr("shell: ");
		if (bang->x)
			ft_putnbr(bang->x);
		else if (bang->c_x)
			ft_putchar(bang->c_x);
		ft_putchar('-');
		if (bang->y)
			ft_putnbr(bang->y);
		else if (bang->c_y)
			ft_putchar(bang->c_y);
		ft_putendl(": bad word specifier");
		return (NULL);
	}


	// MALLOC AND DUP USEFUL
	if (!(result = (char **)malloc(sizeof(char *) * (end - begin + 2))))
		return (NULL);
	i = 0;
	while (hist_line[begin + i] && (begin + i) <= end)
	{
		result[i] = ft_strdup(hist_line[begin + i]);
		i++;
	}
	result[i] = NULL;


	//	TEST
	ft_putstr("Begin == ");
	ft_putnbr(begin);
	ft_putstr("\nEnd == ");
	ft_putnbr(end);
	ft_putchar('\n');
	i = 0;
	while (result[i])
	{
		ft_putendl(result[i]);
		i++;
	}
	i = 0;
	while (hist_line[i])
	{
		ft_strdel(&hist_line[i]);
		i++;
	}
	free(hist_line);
	ft_putendl("Ends here");
	// END TEST
	return (result);
}