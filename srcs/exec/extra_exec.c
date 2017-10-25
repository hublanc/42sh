/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:22:31 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/25 15:28:08 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			*singleton_status(void)
{
	static int	status = 0;

	return (&status);
}

void		add_quote_content(char *str, char *new, int *i, int *j, int len)
{
	char	c;

	c = str[(*i)++];
	while (str[*i] && str[*i] != c && *j < len)
	{
		if (str[*i] == '\\' && str[*i + 1]
			&& ((str[*i + 1] == '"' && c == '"')
				|| str[*i + 1] == '$'))
			(*i)++;
		new[(*j)++] = str[(*i)++];
	}
}
