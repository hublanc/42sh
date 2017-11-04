/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_modifiers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 14:19:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/04 15:12:25 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**do_modifiers(char **tab, t_bang2 *bang)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	if (!tab || !tab[0] || !bang || (!bang->m_h && !bang->m_t && !bang->m_r
			&& !bang->m_e && !bang->m_q && !bang->m_x && !bang->m_s))
		return (tab);
	i = 0;
	tmp = ft_strjoin(tab[0], " ");
	while (tab[++i])
	{
		tmp2 = ft_strjoin(tmp, tab[i]);
		tmp ? free(tmp) : 0;
		tmp = tab[i + 1] ? ft_strjoin(tmp2, " ") : ft_strdup(tmp2);
		free(tmp2);
	}
	printf("\n%s\n", tmp);
	if (bang->m_h)
		rmpathname(&tmp);
	else if (bang->m_t)
		rmpathcomp(&tmp);
	else if (bang->m_r)
		rmsuffix(&tmp);
	else if (bang->m_e)
		rmallbutsuffix(&tmp);
	else if (bang->m_q)
	{
		tmp2 = quoteit(tmp);
		free(tmp);
		tmp = tmp2;
	}
	else if (bang->m_x)
	{
		tmp2 = quoteword(tmp);
		free(tmp);
		tmp = tmp2;
	}
	else if (bang->m_s)
	{
		tmp2 = modif_substi(tmp, bang->old, bang->new, bang->m_g);
		free(tmp);
		tmp = tmp2;
	}
	printf("\n%s\n", tmp);
	del_tabstr(&tab);
	tab = bang_split(tmp);
	free(tmp);
	return (tab);
}
