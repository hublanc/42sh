/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 18:29:18 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 19:29:10 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	rmpathname(char **arg)
{
	int		i;

	if (!arg || !*arg)
		return ;
	i = ft_strlen(*arg) - 1;
	if (i < 0 || !ft_strchr(*arg, '/'))
		return ;
	while ((*arg)[i] != '/')
		ssupprchr(arg, i--);
	(*arg)[i] == '/' ? ssupprchr(arg, i) : 0;
}

void	rmpathcomp(char **arg)
{
	if (!arg || !*arg)
		return ;
	if (!ft_strchr(*arg, '/'))
		return ;
	while (ft_strchr(*arg + 1, '/'))
		ssupprchr(arg, 0);
	ssupprchr(arg, 0);
}

void	rmsuffix(char **arg)
{
	int		i;

	if (!arg || !*arg)
		return ;
	i = ft_strlen(*arg) - 1;
	if (i < 0 || !ft_strchr(*arg, '.'))
		return ;
	while ((*arg)[i] != '.')
		ssupprchr(arg, i--);
	(*arg)[i] == '.' ? ssupprchr(arg, i) : 0;
}

void	rmallbutsuffix(char **arg)
{
	if (!arg || !*arg)
		return ;
	if (!ft_strchr(*arg, '.'))
		return ;
	while (ft_strchr(*arg + 1, '.'))
		ssupprchr(arg, 0);
}

char	*quoteit(char *arg)
{
	char	*s;
	int		i;

	if (!arg)
		return (NULL);
	i = ft_strlen(arg) + 3;
	if (!(s = (char *)ft_memalloc(sizeof(char) + i)))
		return (NULL);
	s[0] = '\'';
	ft_strcat(s, arg);
	ft_strcat(s, "'");
	return (s);
}
