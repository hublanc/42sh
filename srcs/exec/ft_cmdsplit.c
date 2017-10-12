/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:56:19 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/05 14:35:30 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			spend_quote(char *str, int j)
{
	int			i;
	char		c;

	c = str[j];
	i = 1;
	while (str[j + i] && str[j + i] != c)
		i++;
	return (i);
}

static int			countword(char *str)
{
	int		nb_w;
	int		isw;
	int		i;

	i = 0;
	isw = 0;
	nb_w = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '"')
				i += spend_quote(str, i);
			i++;
			isw = 1;
		}
		nb_w += isw == 1 ? 1 : 0;
		isw = 0;
	}
	return (nb_w);
}

static int			getlen(char *str)
{
	int		len;
	char	c;

	len = 0;
	if (*str == '\'' || *str == '"')
	{
		c = *str;
		str++;
		while (*str && *str != c)
		{
			len++;
			str++;
		}
	}
	while (*str && *str != ' ')
	{
		len++;
		str++;
	}
	return (len);
}

static char			*cmdsub(char *str, int *i, int len)
{
	char	*new;
	char	c;
	int		j;

	j = 0;
	if (!str || !(new = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			c = str[(*i)++];
			while (str[*i] != c)
				new[j++] = str[(*i)++];
		}
		else if (str[*i] == '\\')
			new[j++] = str[((*i)++) + 1];
		else
			new[j++] = str[*i];
		(*i)++;
	}
	new[j] = '\0';
	return (new);
}

char				**ft_cmdsplit(char *str)
{
	char		**new;
	int			i;
	int			j;
	int			nb_w;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	nb_w = countword(str);
	if (!(new = (char**)malloc(sizeof(char*) * (nb_w + 1))))
		return (NULL);
	while (nb_w--)
	{
		while (str[j] && str[j] == ' ')
			j++;
		new[i] = cmdsub(str, &j, getlen(str + j));
		i++;
	}
	new[i] = NULL;
	return (new);
}
