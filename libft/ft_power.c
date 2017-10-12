/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:30:58 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/13 14:42:20 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_power(int nb, int pow)
{
	int	result;

	result = 1;
	if (pow == 0)
		return (1);
	if (nb == 0)
		return (0);
	while (pow > 0)
	{
		result = result * nb;
		pow--;
	}
	return (result);
}
