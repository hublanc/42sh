/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:17:33 by hublanc           #+#    #+#             */
/*   Updated: 2016/11/10 16:34:42 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*createstr(unsigned int nb, int len, int isneg)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	if (isneg == 1)
		str[0] = '-';
	return (str);
}

char		*ft_itoa(int n)
{
	unsigned int	nb;
	int				len;
	int				isneg;

	len = 1;
	isneg = 0;
	nb = n;
	if (n < 0)
	{
		isneg = 1;
		nb = -n;
		len++;
		n = -n;
	}
	while (n /= 10)
		len++;
	return (createstr(nb, len, isneg));
}
