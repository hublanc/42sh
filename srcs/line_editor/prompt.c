/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:46:11 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/02 10:26:17 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*split_prompt(char *str)
{
	int		i;
	int		count_slash;
	char	*ret;

	count_slash = 0;
	i = ft_strlen(str);
	while (count_slash != 2 && i--)
	{
		if (str[i] == '/')
			count_slash += 1;
	}
	ret = ft_strsub(str, i + 1, ft_strlen(str));
	(str) ? ft_strdel(&str) : 0;
	return (ret);
}

int		print_prompt(void)
{
	int		size;
	char	*pwd;
	char	*swap;
	char	*hostname;

	pwd = NULL;
	hostname = NULL;
	(!(swap = (char*)ft_memalloc(sizeof(char) * 256))) ? exit(0) : 0;
	pwd = split_prompt(getcwd(pwd, 2048));
	ft_putstr_fd("\x1B[32;1m", 2);
	ft_putstr_fd("21sh@", 2);
	gethostname(swap, 255);
	hostname = ft_strsub(swap, 0, ft_strlen(swap) - 6);
	size = ft_strlen(hostname) + 1;
	(swap) ? ft_strdel(&swap) : 0;
	ft_putstr_fd(hostname, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd("\x1B[36;0m\x1B[34;1m", 2);
	size += ft_strlen(pwd);
	ft_putstr_fd(pwd, 2);
	ft_putstr_fd("\x1B[36;0m", 2);
	ft_putstr_fd(" >> ", 2);
	(hostname) ? ft_strdel(&hostname) : 0;
	(pwd) ? ft_strdel(&pwd) : 0;
	size += 14;
	return (size);
}

char	*return_prompt(void)
{
	char	*pwd;
	char	*swap;
	char	*hostname;
	char	*ret;

	pwd = NULL;
	hostname = NULL;
	(!(swap = (char*)ft_memalloc(sizeof(char) * 256))) ? exit(0) : 0;
	pwd = split_prompt(getcwd(pwd, 2048));
	ret = ft_strdup("21sh@");
	gethostname(swap, 255);
	hostname = ft_strsub(swap, 0, ft_strlen(swap) - 6);
	(swap) ? ft_strdel(&swap) : 0;
	ret = ft_realloc(ret, ft_strlen(hostname));
	ret = ft_strcat(ret, hostname);
	ret = ft_realloc(ret, 1);
	ret = ft_strcat(ret, " ");
	ret = ft_realloc(ret, ft_strlen(pwd) + 4);
	ret = ft_strcat(ret, pwd);
	ret = ft_strcat(ret, " >> ");
	(hostname) ? ft_strdel(&hostname) : 0;
	(pwd) ? ft_strdel(&pwd) : 0;
	return (ret);
}
