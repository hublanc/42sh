/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:49:56 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 19:12:59 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*add_handspace(const char *name)
{
	char	*s;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (name[++i])
		if (name[i] == 32)
			j++;
	s = (char *)ft_memalloc(ft_strlen(name) + j);
	ft_strcat(s, name);
	i = -1;
	while (s[++i])
		if (s[i] == 32)
			saddchr(&s, '\\', i++);
	return (s);
}

static int	do_substitue(char **cmmd, int i, int j, char **tmp2)
{
	t_loc	*loc;
	char	***env;
	char	*tmp;

	env = save_env(NULL);
	if (*tmp2 && (*tmp2)[0] && (((tmp = get_elem(env, *tmp2)) && *(++tmp))
				|| ((loc = get_loc(*tmp2)) && (tmp = loc->value))))
	{
		free(*tmp2);
		*tmp2 = ft_strndup(*cmmd, i);
		tmp = ft_strjoin(*tmp2, add_handspace(tmp));
		(*tmp2) ? free(*tmp2) : 0;
		*tmp2 = ft_strjoin(tmp, *cmmd + j);
		(tmp) ? free(tmp) : 0;
		(*tmp2) ? free(*cmmd) : 0;
		(*tmp2) ? *cmmd = ft_strdup(*tmp2) : 0;
		return (1);
	}
	return (0);
}

static int	substitute(char **cmmd, int i, int j, int is_redir)
{
	char	*tmp2;

	tmp2 = ft_strndup(*cmmd + i + 1, j - i - 1);
	if (!do_substitue(cmmd, i, j, &tmp2))
	{
		if (is_redir)
		{
			print_error(8, tmp2);
			(tmp2) ? free(tmp2) : 0;
			return (-1);
		}
		else
			while (j-- > i)
				ssupprchr(cmmd, i);
	}
	(tmp2) ? free(tmp2) : 0;
	return (1);
}

int			substitution(char **cmmd, int is_redir)
{
	int		i;
	int		j;

	if (!cmmd || !*cmmd)
		return (0);
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
			if (substitute(cmmd, i, j, is_redir) == -1)
				return (-1);
	}
	return (1);
}
