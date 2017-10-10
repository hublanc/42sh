/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 14:11:16 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/10 12:59:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_elem(char ***env, char *elem)
{
	int	i;

	if (!env || !*env || !**env)
		return (NULL);
	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], elem, ft_strlen(elem)))
		i++;
	if (!(*env)[i])
		return (NULL);
	return ((*env)[i] + ft_strlen(elem));
}

void	ssupprchr(char **s, int pos)
{
	int i;

	pos--;
	i = ft_strlen(*s) - 1;
	while (++pos <= i)
		(*s)[pos] = (*s)[pos + 1];
}

void	saddchr(char **s, char c, int pos)
{
	int i;

	i = ft_strlen(*s) + 1;
	while (--i >= pos)
		(*s)[i + 1] = (*s)[i];
	(*s)[pos] = c;
}
