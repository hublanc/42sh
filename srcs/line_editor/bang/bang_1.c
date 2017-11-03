/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:28:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 17:18:01 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	return (NULL);
}

char			*deal_bang(char *cmd, t_control *hist)
{
	char		c;
	char		*new;

	c = 0;
	ft_putcolor("BEGIN :");
	ft_putendl(hist->begin->name);
	ft_putcolor("END :");
	ft_putendl(hist->end->name);
	exit(0);
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
