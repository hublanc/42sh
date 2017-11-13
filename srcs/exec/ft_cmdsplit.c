/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 15:56:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:07:52 by amazurie         ###   ########.fr       */
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
	{
		if (str[j + i] == '\\' && str[j + i + 1] == '\\' && c == '"')
			i++;
		i++;
	}
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
	while (i < INT_MAX - 1 && str[i])
	{
		while (i < INT_MAX - 1 && str[i] && str[i] == ' ')
			i++;
		while (i < INT_MAX - 1 && str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '"')
				i += spend_quote(str, i);
			else if (str[i] == '\\')
				i++;
			(str[i]) ? i++ : 0;
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
	while (str && *str && *str != ' ')
	{
		if (*str == '\'' || *str == '"')
		{
			c = *str;
			str++;
			while (*str && *str != c)
			{
				if (*str == '\\' && *(str + 1) == '\\' && c == '"')
					str++;
				len++;
				str++;
			}
		}
		else if (*str == '\\')
			str++;
		len++;
		*str ? str++ : 0;
	}
	return (len);
}

static char			*cmdsub(char *str, int *i, int len)
{
	char	*new;
	int		j;

	j = 0;
	if (!str || !(new = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[*i] && str[*i] != ' ' && j < len)
	{
		if (str[*i] == '\'' || str[*i] == '"')
			add_quote_content(str, new, i, &j);
		else if (str[*i] == '\\')
			new[j++] = str[++(*i)];
		else
			new[j++] = str[*i];
		str[*i] ? ++*i : 0;
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
