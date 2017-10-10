/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:49:56 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/10 16:21:45 by amazurie         ###   ########.fr       */
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

void	substitution(char **cmmd, char ***env)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	if (!cmmd || !*cmmd)
		return ;
	i = -1;
	while ((*cmmd)[++i])
	{
		if ((*cmmd)[i] == '\'')
			while ((*cmmd)[i] && (*cmmd)[++i] != '\'');
		j = i;
		if ((*cmmd)[i] == '$')
			while ((*cmmd)[j] && (*cmmd)[j] != 32 && (*cmmd)[j] != 9 && (*cmmd)[j] != '\n')
				j++;
		if (j > 0)
		{
			tmp2 = ft_strndup(*cmmd + i, j - i);
			//futur ajout local
			if ((tmp = get_elem(env, tmp2)) && ++tmp)
			{
			}
			else
				while (j-- > i)
					ssupprchr(cmmd, i);
			free(tmp2);
		}
	}
}
