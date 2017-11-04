/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:15:27 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 19:18:21 by hublanc          ###   ########.fr       */
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
			j = ft_strlen(arg + *i) - 1;
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
	int			i;
	int			j;
	int			k;

	if (!arg)
		return (NULL);
	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] == ' ' && (i <= 0 || arg[i - 1] == ' '))
			j += arg[i + 1] ? 3 : 2;
		else if (arg[i] != ' ')
		{
			while (arg[i + 1] && arg[i + 1] != ' ')
				i++;
			j += arg[i + 1] ? 3 : 2;
		}
	}
	if (!(s = (char *)ft_memalloc(sizeof(char) + i + j + 1)))
		return (NULL);
	i = -1;
	k = ft_strlen(arg) - 1;
	while (++i < k)
		quoteword2(arg, &s, &i, k);
	return (s);
}
