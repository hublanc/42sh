/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:42:39 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/31 14:06:56 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		put_my_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int		read_singleton(int sig)
{
	static int	data;

	if (sig == -1)
		return (data);
	else
		data = sig;
	return (0);
}

int		get_read_opt(char **cmd)
{
	int	size;
	int	ret;
	int	opt;

	opt = 0;
	size = 0;
	while (cmd[size])
		size++;
	while ((ret = ft_getopt(size, (const char**)cmd, "r")) != -1)
		opt = ret;
	return (opt);
}

int		valid_local_var(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
			{
				ft_putstr("\n42sh: read: `");
				ft_putstr(cmd[i]);
				ft_putendl("': not a valid identifier");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
