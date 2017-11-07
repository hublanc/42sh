/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_hist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:11:12 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 16:40:26 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	**strsearch(t_control *hist, t_bang2 *bang)
{
	t_lst		*tmp;

	if (!hist)
		tmp = NULL;
	else
		tmp = hist->begin;
	while (tmp
			&& ft_strncmp(tmp->name, bang->str, ft_strlen(bang->str)))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putstr_fd("shell: !", 2);
		ft_putstr_fd(bang->str, 2);
		ft_putstr_fd(": event not found", 2);
		return (NULL);
	}
	return (bang_split(tmp->name));
}

static char	**q_marksearch(t_control *hist, t_bang2 *bang)
{
	t_lst	*tmp;

	if (!hist)
		tmp = NULL;
	else
		tmp = hist->begin;
	while (tmp && !ft_strstr(tmp->name, bang->str))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_putstr_fd("shell: !?", 2);
		ft_putstr_fd(bang->str, 2);
		ft_putstr_fd(": event not found", 2);
		return (NULL);
	}
	return (bang_split(tmp->name));
}

static char	**d_bangsearch(t_control *hist)
{
	t_lst		*tmp;

	if (!hist)
		tmp = NULL;
	else
		tmp = hist->begin;
	if (!tmp)
	{
		ft_putstr_fd("shell: !!: event not found", 2);
		return (NULL);
	}
	return (bang_split(tmp->name));
}

static char	**get_htagstr(char *cmd)
{
	char		*new;
	char		**tab;

	new = NULL;
	while (cmd && *cmd && *cmd != '!')
	{
		new = ft_str_chr_cat(new, *cmd);
		cmd++;
	}
	tab = bang_split(new);
	ft_strdel(&new);
	return (tab);
}

char		**get_line_history(t_control *hist, t_bang2 *bang,
			char *final)
{
	if (bang->hash_t)
		return (get_htagstr(final));
	else if (bang->n_set)
		return (get_nline(hist, bang));
	else if (bang->d_bang)
		return (d_bangsearch(hist));
	else if (bang->q_mark && bang->str)
		return (q_marksearch(hist, bang));
	else if (bang->str)
		return (strsearch(hist, bang));
	return (NULL);
}
