/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_modifiers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:19:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/04 23:47:09 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		bang_s(char **tmp, char **tmp2, t_bang2 *bang)
{
	if (!bang->old || !*(bang->old) || !ft_strstr(*tmp, bang->old))
	{
		ft_putendl("42sh: substitution failed");
		return (0);
	}
	*tmp2 = modif_substi(*tmp, bang->old, bang->new, bang->m_g);
	ft_strdel(tmp);
	if (!(*tmp2))
		return (0);
	*tmp = *tmp2;
	return (1);
}

static int		treat_modifiers(char **tmp, char **tmp2, t_bang2 *bang)
{
	if (bang->m_h)
		rmpathname(tmp);
	else if (bang->m_t)
		rmpathcomp(tmp);
	else if (bang->m_r)
		rmsuffix(tmp);
	else if (bang->m_e)
		rmallbutsuffix(tmp);
	else if (bang->m_q)
	{
		*tmp2 = quoteit(*tmp);
		ft_strdel(tmp);
		*tmp = *tmp2;
	}
	else if (bang->m_x)
	{
		*tmp2 = quoteword(*tmp);
		ft_strdel(tmp);
		*tmp = *tmp2;
	}
	else if (bang->m_s)
		return (bang_s(tmp, tmp2, bang));
	return (1);
}

static char		**del_tab_null(char **tab)
{
	del_tabstr(&tab);
	return (NULL);
}

char			**do_modifiers(char **tab, t_bang2 *bang)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	if (!tab || !tab[0] || !bang || (!bang->m_h && !bang->m_t && !bang->m_r
			&& !bang->m_e && !bang->m_q && !bang->m_x && !bang->m_s))
		return (tab);
	i = 0;
	tmp = tab[1] ? ft_strjoin(tab[0], " ") : ft_strdup(tab[0]);
	while (tab[++i])
	{
		tmp2 = ft_strjoin(tmp, tab[i]);
		tmp ? free(tmp) : 0;
		tmp = tab[i + 1] ? ft_strjoin(tmp2, " ") : ft_strdup(tmp2);
		free(tmp2);
	}
	if (!treat_modifiers(&tmp, &tmp2, bang))
	{
		ft_strdel(&tmp);
		return (del_tab_null(tab));
	}
	del_tabstr(&tab);
	tab = bang_split(tmp);
	ft_strdel(&tmp);
	return (tab);
}
