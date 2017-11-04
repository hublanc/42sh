/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_modifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:40:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 14:25:10 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_smodif(char *cmd, t_bang2 *bang, int i)
{
	char	t;
	int		j;

	t = cmd[++i];
	j = 0;
	while (cmd[i] && (cmd[i] != ' ' || cmd[i - 1] == '\\') && !bang->new)
	{
		if (cmd[i] == t && cmd[i - 1] != '\\' && !bang->old)
			bang->old = ft_strndup(cmd + (i - j), j);
		else if (cmd[i] == t && cmd[i - 1] != '\\')
			bang->new = ft_strndup(cmd + (i - j), j);
		if (cmd[i] == t && cmd[i - 1] != '\\')
			j = -1;
		i++;
		j++;
	}
	if (bang->old && !bang->new)
		bang->new = ft_strndup(cmd + (i - j), j);
}

int			word_modifier(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i] || cmd[i] != ':')
		return (i);
	while (cmd[i] && (cmd[i] == ':' || bang->m_g == 1))
	{
		i++;
		if (cmd[i] && cmd[i] == 'h')
			bang->m_h++;
		else if (cmd[i] && cmd[i] == 't')
			bang->m_t = 1;
		else if (cmd[i] && cmd[i] == 'r')
			bang->m_r = 1;
		else if (cmd[i] && cmd[i] == 'e')
			bang->m_e = 1;
		else if (cmd[i] && cmd[i] == 'p')
			bang->m_p = 1;
		else if (cmd[i] && cmd[i] == 'q')
			bang->m_q = 1;
		else if (cmd[i] && cmd[i] == 'x')
			bang->m_x = 1;
		else if (cmd[i] && cmd[i] == 's')
			check_smodif(cmd, bang, i);
		else
		{
			ft_putstr("42sh: ");
			ft_putchar(cmd[i]);
			ft_putendl(": unrecognized history modifier");
			return (i);
		}
		if (bang->m_g == 1)
			return (i);
		if (cmd[i] && cmd[i] == 'g')
			bang->m_g = 1;
		cmd[i] ? i++ : 0;
	}
	return (i);
}
