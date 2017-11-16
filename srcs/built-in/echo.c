/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:58:47 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 13:15:34 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	treat_octal(char **tab, int i, int *j)
{
	int		int_octal;
	char	tmp[2];
	int		power;

	*j += 1;
	tmp[1] = '\0';
	power = -1;
	int_octal = 0;
	while (power < 2 && tab[i][*j + power + 1] && tab[i][*j + power + 2]
			&& ft_isdigit(tab[i][*j + power + 2]))
		power++;
	while (power >= 0 && tab[i][*j + 1])
	{
		tmp[0] = tab[i][*j + 1];
		int_octal += ft_atoi(tmp) * ft_power(8, power);
		power--;
		*j += 1;
	}
	ft_putchar(int_octal);
}

static void	treat_str3(char **tab, int i, int *j)
{
	if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == 'v')
	{
		ft_putchar('\v');
		*j += 1;
	}
	else if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == '\\')
		ft_putchar('\\');
	else if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == '0')
		treat_octal(tab, i, j);
	else
		ft_putchar(tab[i][*j]);
}

static int	treat_str2(char **tab, int i, int *j)
{
	if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == 'c')
	{
		return (1);
		*j += 1;
	}
	else if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == 'f')
	{
		ft_putchar('\f');
		*j += 1;
	}
	else if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == 'r')
	{
		ft_putchar('\r');
		*j += 1;
	}
	else if (tab[i][*j] == '\\' && tab[i][*j + 1] && tab[i][*j + 1] == 't')
	{
		ft_putchar('\t');
		*j += 1;
	}
	else
		treat_str3(tab, i, j);
	return (0);
}

static int	treat_str(char **tab, int i)
{
	int	j;

	j = 0;
	while (tab[i][j])
	{
		if (tab[i][j] == '\\' && tab[i][j + 1] && tab[i][j + 1] == 'n')
		{
			ft_putchar('\n');
			j += 1;
		}
		else if (tab[i][j] == '\\' && tab[i][j + 1] && tab[i][j + 1] == 'a')
		{
			ft_putchar('\a');
			j += 1;
		}
		else if (tab[i][j] == '\\' && tab[i][j + 1] && tab[i][j + 1] == 'b')
		{
			ft_putchar('\b');
			j += 1;
		}
		else if (treat_str2(tab, i, &j))
			return (1);
		j++;
	}
	return (0);
}

int			ft_echo(char **tab, t_node *tree)
{
	int		i;
	int		nl;

	i = 1;
	nl = 1;
	if (fcntl(tree->out, F_GETFD) < 0)
	{
		ft_putstr_fd("echo: write error: Bad file descriptor\n", 2);
		return (1);
	}
	if (len_array(tab) > 1)
	{
		nl = !ft_strcmp("-n", tab[1]) ? 0 : 1;
		i += !ft_strcmp("-n", tab[1]) ? 1 : 0;
		while (tab[i])
		{
			if (treat_str(tab, i))
				return (0);
			(tab[i + 1]) ? ft_putchar(' ') : 0;
			i++;
		}
	}
	nl ? ft_putchar('\n') : 0;
	return (0);
}
