/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 15:46:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/27 16:01:29 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t	print_buff(char **buff)
{
	size_t len;

	len = ft_strlen(*buff);
	ft_putstr(*buff);
	ft_bzero(*buff, len);
	return (len);
}

size_t	buffcat(char **buff, char *s)
{
	size_t	len;

	len = 0;
	if (ft_strlen(*buff) + ft_strlen(s) < COMPLBUFF - 1)
		ft_strcat(*buff, s);
	else if (ft_strlen(s) < COMPLBUFF - 1)
	{
		len = print_buff(buff);
		ft_strcat(*buff, s);
	}
	else
	{
		len = print_buff(buff) + ft_strlen(s);
		ft_putstr(s);
	}
	return (len);
}

size_t	buffncat(char **buff, char *s, size_t n)
{
	char	*tmp;
	size_t	len;

	len = 0;
	if (ft_strlen(*buff) + ft_strlen(s) < COMPLBUFF - 1)
		ft_strncat(*buff, s, n);
	else if (ft_strlen(s) < COMPLBUFF - 1)
	{
		len = print_buff(buff);
		ft_strncat(*buff, s, n);
	}
	else
	{
		len = print_buff(buff) + ((ft_strlen(s) >= n) ? n : ft_strlen(s));
		if (!(tmp = ft_strndup(s, n)))
			return (0);
		ft_putstr(tmp);
		free(tmp);
	}
	return (len);
}
