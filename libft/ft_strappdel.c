/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:38:20 by hublanc           #+#    #+#             */
/*   Updated: 2017/01/11 11:38:46 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strappdel(char *dst, char *str)
{
	dst = ft_realloc(dst, ft_strlen(str));
	ft_strcat(dst, str);
	ft_strdel(&str);
	return (dst);
}
