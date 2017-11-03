/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:28:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 16:05:54 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			**get_htagstr(char *cmd)
{
	char		*new;
	char		**tab;

	new = NULL;
	while (cmd && *cmd && *cmd != '!')
	{
		new = ft_str_chr_cat(new, *cmd);
		cmd++;
	}
	tab = ft_cmdsplit(new);
	ft_strdel(&new);
	return (tab);
}

char			**get_nline(t_control *hist, t_bang2 *bang)
{
	t_lst		*tmp;

	tmp = hist->begin;
	ft_putendl(bang->str);
	return (NULL);
}

char			**get_line_history(t_control *hist, t_bang2 *bang, char *final)
{
	if (bang->hash_t)
		return (get_htagstr(final));
	else if (bang->n_set || bang->d_bang)
		return (get_nline(hist, bang));
	return (NULL);
}

char			*begin_bang(char *cmd, t_control *hist, char *final)
{
	t_bang2		*bang;
	char		**line_h_split;

	bang = (t_bang2*)ft_memalloc(sizeof(t_bang2));
	cmd = event_designator(cmd, bang);
	cmd = word_designator_x(cmd, bang);
	cmd = word_designator_y(cmd, bang);
	cmd = word_modifier(cmd, bang);
	line_h_split = get_line_history(hist, bang, final);
	line_h_split = designator_fnc(line_h_split, bang);
	return (NULL);
}

char			*deal_bang(char *cmd, t_control *hist)
{
	char		c;
	char		*new;

	c = 0;
	new = ft_strdup(cmd);
	if (!ft_strchr(cmd, '!'))
		return (NULL);
	while (cmd && *cmd)
	{
		if (*cmd == '!' && *(cmd + 1) && *(cmd + 1) != ' ' && c != '\''
			&& *(cmd + 1) != '\t' && *(cmd + 1) != '=' && *(cmd + 1) != '(')
			new = begin_bang(cmd, hist, new);
		if (*cmd == '\'')
			while (*cmd && *cmd != '\'')
				cmd++;
		if (*cmd == '\\')
			cmd++;
		*cmd ? cmd++ : 0;
	}
	return (new);
}
