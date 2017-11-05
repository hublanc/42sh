/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:38:20 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/11 11:38:46 by lbopp            ###   ########.fr       */
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
