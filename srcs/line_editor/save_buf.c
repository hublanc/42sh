/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 10:53:18 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:19:28 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*save_buf(char *buf)
{
	static char *s_buf = NULL;

	if (buf)
	{
		if (ft_strlen(buf) <= 5)
		{
			if (!(s_buf = (char*)ft_memalloc(6)))
			{
				s_buf = NULL;
			}
			ft_strcat(s_buf, buf);
		}
		else
			s_buf = ft_strdup(buf);
	}
	return (s_buf);
}
