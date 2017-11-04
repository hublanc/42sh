/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_modifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:40:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 13:33:02 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			word_modifier(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i] || cmd[i] != ':')
		return (i);
	while (cmd[i] && cmd[i] == ':')
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
		cmd[i] ? i++ : 0;
	}
	return (i);
}
