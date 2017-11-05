/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:30:54 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/10 18:57:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	if (*alst)
	{
		ft_lstdel(&((*alst)->next), del);
		ft_lstdelone(alst, del);
	}
}
