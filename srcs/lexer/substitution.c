/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:49:56 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 10:24:27 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ssupprchr(char **s, int pos)
{
	int	i;

	pos--;
	i = ft_strlen(*s)	- 1;
	while (++pos <= i)
		(*s)[pos] = (*s)[pos + 1];
}

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

static void	substitute(char **cmmd, char ***env, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strndup(*cmmd + i + 1, j - i - 1);
	//futur ajout local
	if (tmp2 && tmp2[0] && (tmp = get_elem(env, tmp2)) && *(++tmp))
	{
		free(tmp2);
		tmp2 = ft_strndup(*cmmd, i);
		tmp = ft_strjoin(tmp2, tmp);
		(tmp2) ? free(tmp2) : 0;
		tmp2 = ft_strjoin(tmp, *cmmd + j);
		(tmp) ? free(tmp) : 0;
		(tmp2) ? free(*cmmd) : 0;
		(tmp2) ? *cmmd = ft_strdup(tmp2) : 0;
	}
	else
		while (j-- > i)
			ssupprchr(cmmd, i);
	(tmp2) ? free(tmp2) : 0;
}

void		substitution(char **cmmd, char ***env)
{
	int		i;
	int		j;

	if (!cmmd || !*cmmd)
		return ;
	i = -1;
	while ((*cmmd)[++i])
	{
		if ((*cmmd)[i] == '\'')
			while ((*cmmd)[i] && (*cmmd)[++i] != '\'');
		j = i + 1;
		if ((*cmmd)[i] == '$')
			while ((*cmmd)[j] && (*cmmd)[j] != 32 && (*cmmd)[j] != 9
					&& (*cmmd)[j] != '\n' && (*cmmd)[j] != '"'
					&& (*cmmd)[j] != '$')
				j++;
		if (j > i + 1)
			substitute(cmmd, env, i, j);
	}
}
