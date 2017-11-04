/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_modifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 13:40:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 18:28:21 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	arr_bangsubs(void)
{
	ft_putendl("42sh: no previous substitution");
	return (-1);
}

static int	check_smodif(char *cmd, t_bang2 *bang, int i)
{
	char	t;
	int		j;

	bang->old = NULL;
	bang->new = NULL;
	t = cmd[++i];
	j = 0;
	bang->m_s = 1;
	while (cmd[++i] && (cmd[i] != ' ' || cmd[i - 1] == '\\') && !bang->new)
	{
		if (cmd[i] == t && cmd[i - 1] != '\\' && !bang->old)
		{
			if (j <= 0)
				return (arr_bangsubs());
			bang->old = ft_strndup(cmd + (i - j), j);
		}
		else if (cmd[i] == t && cmd[i - 1] != '\\' && bang->old)
			bang->new = ft_strndup(cmd + (i - j), j);
		if (cmd[i] == t && cmd[i - 1] != '\\')
			j = -1;
		j++;
	}
	if (bang->old && !bang->new && i - j > 0)
		bang->new = ft_strndup(cmd + (i - j), j);
	return (i);
}

static int	error_modifier(char c)
{
	ft_putstr("42sh: ");
	ft_putchar(c);
	ft_putendl(": unrecognized history modifier");
	return (-1);
}

static int	fill_bang(char *cmd, int i, t_bang2 *bang)
{
	if (cmd[i] && cmd[i] == 'h')
		bang->m_h = 1;
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
	{
		if ((i = check_smodif(cmd, bang, i)) == -1)
			return (-1);
	}
	else if (cmd[i] && cmd[i] != 'g')
		return (error_modifier(cmd[i]));
	return (i);
}

int			word_modifier(char *cmd, t_bang2 *bang, int i)
{
	if (!cmd || !cmd[i] || cmd[i] != ':')
		return (i);
	while (cmd[i] && (cmd[i] == ':' || bang->m_g == 1))
	{
		i++;
		if ((i = fill_bang(cmd, i, bang)) == -1)
			return (-1);
		if (bang->m_g == 1)
			return (i + 1);
		if (cmd[i] && cmd[i] == 'g')
			bang->m_g = 1;
		cmd[i] && !bang->m_s && !bang->m_g ? i++ : 0;
	}
	return (i);
}
