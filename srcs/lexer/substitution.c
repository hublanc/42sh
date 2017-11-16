/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 15:49:56 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/05 13:27:34 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	do_substitue(char **cmmd, int i, int j, char **tmp2)
{
	char	*tmp;
	char	*tmp3;

	if ((tmp = test_cansubsti(tmp2)))
	{
		ft_strdel(tmp2);
		*tmp2 = ft_strndup(*cmmd, i);
		tmp3 = add_handspace(tmp);
		if (tmp3 == NULL)
			return (0);
		tmp = ft_strjoin(*tmp2, tmp3);
		ft_strdel(&tmp3);
		(*tmp2) ? ft_strdel(tmp2) : 0;
		*tmp2 = ft_strjoin(tmp, *cmmd + j);
		(tmp) ? ft_strdel(&tmp) : 0;
		(*tmp2) ? ft_strdel(cmmd) : 0;
		(*tmp2) ? *cmmd = ft_strdup(*tmp2) : 0;
		return (1);
	}
	return (0);
}

static int	substitute(char **cmmd, int i, int j, int is_redir)
{
	char	*tmp2;

	if (j - i - 1 <= 0)
		return (0);
	tmp2 = ft_strndup(*cmmd + i + 1, j - i - 1);
	if (!do_substitue(cmmd, i, j, &tmp2))
	{
		if (is_redir)
		{
			print_error(8, tmp2);
			(tmp2) ? ft_strdel(&tmp2) : 0;
			return (-1);
		}
		else
			while (j-- > i)
				ssupprchr(cmmd, i);
	}
	(tmp2) ? ft_strdel(&tmp2) : 0;
	return (1);
}

static int	quote_substitution(char **cmmd, int *i, int *j, int is_redir)
{
	while ((*cmmd)[*i] && (*cmmd)[++*i] && (*cmmd)[*i] != '"')
	{
		*j = *i + 1;
		*i += (*cmmd)[*i] == '\\' ? 1 : 0;
		if ((*cmmd)[*i] == '$')
			while ((*cmmd)[*j] && (*cmmd)[*j] != 32 && (*cmmd)[*j] != 9
			&& (*cmmd)[*j] != '\n' && (*cmmd)[*j] != '"'
			&& (*cmmd)[*j] != '$' && (*cmmd)[*j] != '\\')
				(*j)++;
		if (*j > *i + 1)
			if (substitute(cmmd, *i, *j, is_redir) == -1)
				return (-1);
	}
	return (0);
}

static void	substitution2(char *cmmd, int i, int *j)
{
	if (cmmd[i] && cmmd[i] == '$')
		while (cmmd[*j] && cmmd[*j] != 32 && cmmd[*j] != 9
			&& cmmd[*j] != '\n' && cmmd[*j] != '"'
			&& cmmd[*j] != '$' && cmmd[*j] != '\\' && cmmd[*j] != '/'
			&& cmmd[*j] != ':' && cmmd[*j] != '@')
			*j += 1;
}

int			substitution(char **cmmd, int is_redir)
{
	int		i;
	int		j;

	if (!cmmd || !*cmmd)
		return (0);
	i = -1;
	while (cmmd && *cmmd && (*cmmd)[++i])
	{
		if ((*cmmd)[i] == '\'')
			while ((*cmmd)[++i] && (*cmmd)[i] != '\'')
				;
		if ((*cmmd)[i] == '"')
			if (quote_substitution(cmmd, &i, &j, is_redir) == -1)
				return (-1);
		j = i + 1;
		i += (*cmmd)[i] == '\\' ? 1 : 0;
		substitution2(*cmmd, i, &j);
		if (j > i + 1 || !(*cmmd)[i])
		{
			if (!(*cmmd)[i] || substitute(cmmd, i, j, is_redir) == -1)
				return (-1);
			i = -1;
		}
	}
	return (0);
}
