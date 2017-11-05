/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:15:27 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/05 12:15:12 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	quoteword2(char *arg, char **s, int *i, int k)
{
	int		j;

	if (arg[*i] == ' ' && (*i <= 0 || arg[*i - 1] == ' '))
		arg[*i + 1] ? ft_strcat(*s, "'' ") : ft_strcat(*s, "''");
	else if (arg[*i] != ' ')
	{
		if (!(j = ft_strlen_chr(arg + *i, ' ')))
			j = ft_strlen(arg + *i);
		ft_strcat(*s, "'");
		ft_strncat(*s, arg + *i, j);
		ft_strcat(*s, "'");
		*i += j;
		(*i < k && arg[*i + 1]) ? ft_strcat(*s, " ") : 0;
	}
}

char		*quoteword(char *arg)
{
	char		*s;
	int			i[3];

	if (!arg)
		return (NULL);
	i[0] = -1;
	i[1] = 0;
	while (arg[++i[0]])
	{
		if (arg[i[0]] == ' ' && (i[0] <= 0 || arg[i[0] - 1] == ' '))
			i[1] += arg[i[0] + 1] ? 3 : 2;
		else if (arg[i[0]] != ' ')
		{
			while (arg[i[0] + 1] && arg[i[0] + 1] != ' ')
				i[0]++;
			i[1] += arg[i[0] + 1] ? 3 : 2;
		}
	}
	if (!(s = (char *)ft_memalloc(sizeof(char) + i[0] + i[1] + 1)))
		return (NULL);
	i[0] = -1;
	i[2] = ft_strlen(arg);
	while (++i[0] < i[2])
		quoteword2(arg, &s, &(i[0]), i[2]);
	return (s);
}
