/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:28:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 20:42:39 by hublanc          ###   ########.fr       */
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
		i++;
	}
	tmp = ft_strsub(final, bang->end, ft_strlen(final));
	new = ft_strapp(new, tmp);
	ft_strdel(&tmp);
	ft_strdel(&final);
	return (new);
}

int				begin_bang(t_control *hist, char **final, int i)
{
	t_bang2		*bang;
	char		**tab;

	bang = (t_bang2*)ft_memalloc(sizeof(t_bang2));
	bang->begin = i;
	i = event_designator(*final, bang, i);
	i = word_designator_x(*final, bang, i);
	i = word_designator_y(*final, bang, i);
	i = word_modifier(*final, bang, i);
	bang->end = i;
	if (!(tab = get_line_history(hist, bang, *final))
	|| !(tab = designator_fnc(tab, bang)))
		return (-1);
	*final = replace_str(tab, *final, bang);
	ft_putcolor("LINE : ");
	disp_tab(tab);
	ft_putcolor("STR : ");
	ft_putstr(*final);
	//bangafri
	return (bang->begin);
}

char			*deal_bang(char *cmd, t_control *hist)
{
	char		c;
	char		*new;
	int			i;

	c = 0;
	i = 0;
	new = ft_strdup(cmd);
	if (!ft_strchr(cmd, '!'))
		return (NULL);
	while (new && new[i])
	{
		if (new[i] == '!' && new[i + 1] && new[i + 1] != ' ' && c != '\''
			&& new[i + 1] != '\t' && new[i + 1] != '=' && new[i + 1] != '(')
			if ((i = begin_bang(hist, &new, i)) == -1)
				return (NULL);
		if (new[i] == '\'')
			while (new[i] && new[i] != '\'')
				i++;
		if (new[i] == '\\')
			i++;
		new[i] ? i++ : 0;
	}
	return (new);
}
