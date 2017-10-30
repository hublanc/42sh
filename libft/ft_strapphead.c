/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapphead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/20 21:24:04 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/20 21:31:09 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strapphead(char *str1, char *str2)
{
	char		*new;

	new = NULL;
	new = ft_strapp(new, str2);
	new = ft_strapp(new, str1);
	ft_strdel(&str1);
	return (new);
}
