/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dotdot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 17:00:31 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/30 17:39:34 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_isdotdot(char **tmp)
{
	char	*temp;

	if (ft_strcmp(*tmp, "/"))
	{
		temp = ft_strrchr(*tmp, '/');
		if (!ft_strcmp(temp, *tmp))
			temp[1] = '\0';
		else
			temp[0] = '\0';
	}
}

void		check_dotdot(char **tmp)
{
	int		i;
	char	**split;

	i = 0;
	if (*tmp && (*tmp)[0] == '/')
	{
		split = ft_strsplit(*tmp, '/');
		ft_strdel(&(*tmp));
		*tmp = ft_strdup("/");
		while (split[i])
		{
			if (!ft_strcmp(split[i], ".."))
				check_isdotdot(tmp);
			else if (ft_strcmp(split[i], "."))
			{
				add_slash(&(*tmp));
				*tmp = ft_strapp(*tmp, split[i]);
			}
			i++;
		}
	}
	del_tabstr(&split);
}
