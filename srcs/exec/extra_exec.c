/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:22:31 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:07:00 by amazurie         ###   ########.fr       */
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
		if (str[*i] == '\\' && str[*i + 1] == '\\' && c == '"')
			(*i)++;
		new[(*j)++] = str[(*i)++];
	}
}

int			*singleton_fail(void)
{
	static int		s_fail = 0;

	return (&s_fail);
}

int			get_fail(void)
{
	int		*fail;

	fail = singleton_fail();
	return (*fail);
}

void		reset_var(int *input, int *fd1, int *fd2)
{
	int		*fail;

	fail = singleton_fail();
	if (*input != 0)
		close(*input);
	if (*fd1 != 0)
		close(*fd1);
	if (*fd2 != 1)
		close(*fd2);
	*input = 0;
	*fd1 = 0;
	*fd2 = 1;
	*fail = 0;
}
