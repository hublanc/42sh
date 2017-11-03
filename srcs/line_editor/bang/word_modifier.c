/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_modifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:40:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 16:06:55 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*word_modifier(char *cmd, t_bang2 *bang)
{
	if (!cmd || !*cmd || *cmd != ':')
		return (cmd);
	while (*cmd && *cmd != ':')
	{
		cmd++;
		if (*cmd && *cmd == 'h')
			bang->m_h = 1;
		if (*cmd && *cmd == 't')
			bang->m_t = 1;
		if (*cmd && *cmd == 'r')
			bang->m_r = 1;
		if (*cmd && *cmd == 'e')
			bang->m_e = 1;
		if (*cmd && *cmd == 'p')
			bang->m_p = 1;
		if (*cmd && *cmd == 'q')
			bang->m_q = 1;
		if (*cmd && *cmd == 'x')
			bang->m_x = 1;
		*cmd ? cmd++ : 0;
	}
	return (cmd);
}
