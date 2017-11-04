/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 12:52:22 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/04 17:37:49 by amazurie         ###   ########.fr       */
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
		if (str[j + i] == '\\' && str[j + i + 1] && c == '"'
				&& (str[j + i + 1] == '"' || str[j + i + 1] == '$'))
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
			len++;
			while (*str && *str != c)
			{
				len++;
				str++;
			}
		}
		else if (*str == '\\' && ++len)
			str++;
		len++;
		*str ? str++ : 0;
	}
	return (len);
}

static char			*cmdsub(char *str, int *i, int k, int len)
{
	char	*new;
	char	c;
	int		j;

	j = 0;
	if (!str || !(new = (char*)ft_memalloc(sizeof(char) * len + k + 1)))
		return (NULL);
	ft_strncat(new, str + (*i - k), k);
	k ? j = ft_strlen(new) - 1 : 0;
	while (str[*i] && str[*i] != ' ' && j < len + k)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			c = str[(*i)];
			new[j++] = str[(*i)++];
			while (str[*i] && str[*i] != c)
				new[j++] = str[(*i)++];
			new[j++] = str[(*i)++];
		}
		else
			new[j++] = str[*i];
		str[*i] ? ++*i : 0;
	}
	new[j] = '\0';
	return (new);
}

char				**bang_split(char *str)
{
	char		**new;
	int			i;
	int			j;
	int			k;
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
		k = 0;
		while (str[j] && str[j] == ' ' && (++k))
			j++;
		new[i] = cmdsub(str, &j, k, getlen(str + j));
		i++;
	}
	new[i] = NULL;
	return (new);
}
