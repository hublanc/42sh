/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strapp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:15:48 by hublanc           #+#    #+#             */
/*   Updated: 2017/01/11 11:39:08 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strapp(char *dst, char *str)
{
	dst = ft_realloc(dst, ft_strlen(str));
	ft_strcat(dst, str);
	return (dst);
}
