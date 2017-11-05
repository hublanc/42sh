/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:28:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/05 13:13:33 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*replace_str(char **tab, char *final, t_bang2 *bang)
{
	char	*new;
	char	*tmp;
	int		i;

	new = ft_strsub(final, 0, bang->begin);
	i = 0;
	while (tab && tab[i])
	{
		new = ft_strapp(new, tab[i]);
		if (tab[i + 1])
			new = ft_strapp(new, " ");
		i++;
	}
	tmp = ft_strsub(final, bang->end, ft_strlen(final) - 1);
	new = ft_strapp(new, tmp);
	ft_strdel(&tmp);
	ft_strdel(&final);
	return (new);
}

int				del_bang(t_bang2 *bang)
{
	if (!bang)
		return (-1);
	if (bang->cmd)
		ft_strdel(&(bang->cmd));
	if (bang->str)
		ft_strdel(&(bang->str));
	if (bang->new)
		ft_strdel(&(bang->new));
	if (bang->old)
		ft_strdel(&(bang->old));
	free(bang);
	return (-1);
}

int				begin_bang(t_control *hist, char **final, int i, int *is_p)
{
	t_bang2		*bang;
	char		**tab;

	bang = (t_bang2*)ft_memalloc(sizeof(t_bang2));
	bang->begin = i;
	i = event_designator(*final, bang, i);
	i = word_designator_x(*final, bang, i);
	i = word_designator_y(*final, bang, i);
	if ((i = word_modifier(*final, bang, i)) == -1)
		return (del_bang(bang));
	bang->end = i;
	if (!(tab = get_line_history(hist, bang, *final))
			|| !(tab = designator_fnc(tab, bang))
			|| !(tab = do_modifiers(tab, bang)))
	{
		del_tabstr(&tab);
		return (del_bang(bang));
	}
	*final = replace_str(tab, *final, bang);
	i = bang->begin;
	del_tabstr(&tab);
	*is_p = bang->m_p ? 1 : 0;
	del_bang(bang);
	return (i);
}

char			*end_bang(t_control *hist, char *new, int is_p)
{
	add_hist_or_not(&hist, new);
	ft_putendl(new);
	if (is_p)
		ft_strdel(&new);
	return (new);
}

char			*deal_bang(char *cmd, t_control *hist)
{
	char		c;
	char		*new;
	int			i;
	int			is_p;

	c = 0;
	i = 0;
	is_p = 0;
	if (!ft_strchr(cmd, '!'))
		return (ft_strdup(cmd));
	new = ft_strdup(cmd);
	while (new && new[i])
	{
		if (new[i] == '!' && new[i + 1] && new[i + 1] != ' ' && c != '\''
			&& new[i + 1] != '\t' && new[i + 1] != '=' && new[i + 1] != '(')
			if ((i = begin_bang(hist, &new, i, &is_p)) == -1)
				return (free_str_return_null(&new));
		if (new[i] == '\'')
			while (new[i] && new[i] != '\'')
				i++;
		new[i] && new[i] == '\\' ? i++ : 0;
		new[i] ? i++ : 0;
	}
	new = end_bang(hist, new, is_p);
	return (new);
}
