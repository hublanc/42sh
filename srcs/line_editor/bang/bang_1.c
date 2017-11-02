/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:28:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/02 21:41:56 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*get_bang_str(char *cmd, t_hublanc *bang)
{
	while (cmd && *cmd && *cmd != ':' && *cmd != ' ' && *cmd != '!')
	{
		bang->str = ft_str_chr_cat(bang->str, *cmd);
		cmd++;
	}
	return (cmd);
}

char			*event_designator(char *cmd, t_hublanc *bang)
{
	cmd++;
	if (!cmd || !*cmd)
		return ;
	if (*cmd == '!' && cmd++)
		bang->cmd_l = -1;
	else if (*cmd && ft_isdigit(*cmd))
	{
		bang->cmd_l = ft_atoi(cmd);
		while (*cmd && ft_isdigit(*cmd))
			cmd++;
	}
	else if (*cmd == '#' && cmd++)
		bang->hash_t = 1;
	else if (*cmd == '?')
	{
		bang->q_mark = 1;
		cmd = get_bang_str(cmd, bang);
	}
	else if (*cmd)
		cmd = get_bang_str(cmd, bang);
	return (cmd);
}

char			*word_designator(char *cmd, t_hublanc *bang)
{
	if (!cmd || !*cmd || *cmd != ':')
		return ;
	cmd++;
	if (*cmd == '^')
		bang->x = 1;
	else if (*cmd == '$')
		bang->dollar = 1;

}

char			begin_bang(char *cmd, t_control *hist)
{
	t_hublanc	*bang;

	t_hublanc = (t_hublanc*)ft_memalloc(sizeof(s_hublanc));
	cmd = event_designator(cmd, bang);
	cmd = word_designator(cmd, bang);
}

char			*deal_bang(char *cmd, t_control *hist)
{
	char		c;
	char		*new;

	c = 0;
	new = NULL;
	if (!ft_strchr(cmd, '!'))
		return (NULL);
	while (cmd && *cmd)
	{
		if (*cmd == '!' && *(cmd + 1) && *(cmd + 1) != ' ' && c != '\''
			&& *(cmd + 1) != '\t' && *(cmd + 1) != '=' && *(cmd + 1) != '(')
			new = begin_bang(cmd, hist);
		if (*cmd == '\'')
			while (*cmd && *cmd != '\'')
				cmd++;
		if (*cmd == '\\')
			cmd++;
		*cmd ? cmd++ : 0;
	}
	return (new);
}
