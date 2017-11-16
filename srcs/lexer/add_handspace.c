/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binaries.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 12:18:48 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 10:29:32 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*add_handspace(const char *name)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (name[++i])
		if (name[i] == 32)
			j++;
	if (!(s = (char *)ft_memalloc(ft_strlen(name) + j + 1)))
		return (NULL);
	ft_strcat(s, name);
	i = -1;
	while (s[++i])
		if (s[i] == 32)
			saddchr(&s, '\\', i++);
	return (s);
}

char	*test_cansubsti(char **name)
{
	t_loc	*loc;
	char	***env;
	char	*tmp;
	char	*tmp3;

	tmp3 = ft_strjoin(*name, "=");
	env = save_env(NULL);
	if (*name && (*name)[0] && ((tmp = get_elem(env, tmp3))
			|| ((loc = get_loc(*name))
			&& (tmp = loc->value))))
	{
		free(tmp3);
		return (tmp);
	}
	free(tmp3);
	return (NULL);
}
