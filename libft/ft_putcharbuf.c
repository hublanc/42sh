/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharbuf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 18:28:03 by hublanc           #+#    #+#             */
/*   Updated: 2017/01/19 16:56:55 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*g_buf = NULL;

void		putbuf(void)
{
	ft_putstr(g_buf);
	ft_strclr(g_buf);
}

void		ft_putstrbuf(char *str)
{
	int		len;
	int		i;

	i = 0;
	if (!g_buf)
		g_buf = ft_strnew(BUFF_CHAR);
	len = ft_strlen(g_buf);
	while (str[i])
	{
		if (len == BUFF_CHAR)
		{
			putbuf();
			len = 0;
		}
		g_buf[len++] = str[i++];
	}
}

void		ft_putnstrbuf(char *str, int n)
{
	int		len;
	int		i;

	i = 0;
	if (!g_buf)
		g_buf = ft_strnew(BUFF_CHAR);
	len = ft_strlen(g_buf);
	while (str[i] && n--)
	{
		if (len == BUFF_CHAR)
		{
			putbuf();
			len = 0;
		}
		g_buf[len++] = str[i++];
	}
}

void		ft_putchrbuf(char c)
{
	int		len;

	if (!g_buf)
		g_buf = ft_strnew(BUFF_CHAR);
	len = ft_strlen(g_buf);
	if (len == BUFF_CHAR)
	{
		putbuf();
		len = 0;
	}
	g_buf[len] = c;
}

void		ft_putnbrbuf(intmax_t nb)
{
	uintmax_t	n;

	if (nb < 0)
	{
		n = -nb;
		ft_putchrbuf('-');
	}
	else
		n = nb;
	if (nb / 10 > 0)
		ft_putnbrbuf(n / 10);
	ft_putchrbuf((n % 10) + '0');
}
