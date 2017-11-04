/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_hist2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:15:28 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 17:23:59 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	**endsearch_nl(t_control *hist, t_bang2 *bang)
{
	t_lst	*tmp;
	int		i;

	i = -1;
	tmp = hist->begin;
	while (tmp && i-- > bang->cmd_l)
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putstr_fd("42sh: !", 2);
		ft_putnbr_fd(bang->cmd_l, 2);
		ft_putstr_fd(": event not found\n", 2);
		return (NULL);
	}
	return (ft_cmdsplit(tmp->name));
}

static char	**beginsearch_nl(t_control *hist, t_bang2 *bang)
{
	t_lst	*tmp;
	int		i;

	i = 1;
	tmp = hist->end;
	while (tmp && i++ < bang->cmd_l)
		tmp = tmp->prev;
	if (!tmp)
	{
		ft_putstr_fd("42sh: !", 2);
		ft_putnbr_fd(bang->cmd_l, 2);
		ft_putstr_fd(": event not found\n", 2);
		return (NULL);
	}
	return (ft_cmdsplit(tmp->name));
}

char		**get_nline(t_control *hist, t_bang2 *bang)
{
	if (bang->cmd_l < 0)
		return (endsearch_nl(hist, bang));
	else if (bang->cmd_l > 0)
		return (beginsearch_nl(hist, bang));
	else if (bang->cmd_l == 0 && bang->n_set)
	{
		ft_putstr_fd("42sh: !0: event not found\n", 2);
		return (NULL);
	}
	return (NULL);
}
