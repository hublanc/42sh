/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 14:11:16 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/10 12:59:15 by lbopp            ###   ########.fr       */
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

void	check_isenvpwd(char ***env)
{
	char	*tab[4];
	char	tmp[1025];

	if (get_elem(env, "PWD="))
		return ;
	tab[0] = "setenv";
	tab[1] = "PWD";
	ft_bzero(tmp, 1025);
	getcwd(tmp, 1024);
	tab[2] = tmp;
	tab[3] = 0;
	ft_setenv(tab, env);
}
