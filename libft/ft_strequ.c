/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:43:00 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/14 12:17:51 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int		res;

	if (!s1 || !s2)
		return (0);
	res = ft_strcmp(s1, s2);
	if (res == 0)
		return (1);
	else
		return (0);
}
