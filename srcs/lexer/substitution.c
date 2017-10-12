/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:49:56 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 19:02:19 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
			while ((*cmmd)[i] && (*cmmd)[++i] != '\'')
				;
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
