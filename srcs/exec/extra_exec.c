/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:22:31 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/19 11:55:48 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			*singleton_status(void)
{
	static int	status = 0;

	return (&status);
}

void		add_quote_content(char *str, char *new, int *i, int *j)
{
	char	c;

	c = str[(*i)++];
	while (str[*i] && str[*i] != c)
	{
		if (str[*i] == '\\' && str[*i + 1]
			&& ((str[*i + 1] == '"' && c == '"')
				|| str[*i + 1] == '$'))
			(*i)++;
		new[(*j)++] = str[(*i)++];
	}
}
