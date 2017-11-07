/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimlast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:22:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 18:17:30 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_strtrimlast(char **s, char c)
{
	int		len;
	char	*new;

	if (!s || !(*s) || (*s)[ft_strlen(*s) - 1] != c)
		return ;
	len = ft_strlen(*s) - 1;
	while (len && (*s)[len] == c)
		len--;
	new = ft_strsub(*s, 0, len + 1);
	ft_strdel(s);
	*s = new;
}
