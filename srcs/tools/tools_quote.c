/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 13:27:31 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/11 21:20:07 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*pass_quote(char *s, char c)
{
	s++;
	while (*s && *s != c)
		s++;
	return (s);
}

static int			count_word(char *s)
{
	int		isw;
	int		nb;

	isw = 0;
	nb = 0;
	while (*s)
	{
		if (!isw && *s != ' ')
		{
			isw = 1;
			nb += 1;
		}
		if (*s == '\'' || *s == '"')
			s = pass_quote(s, *s);
		if (isw && *s && *s == ' ')
			isw = 0;
		*s ? s++ : 0;
	}
	return (nb);
}

static int			get_len(char *s)
{
	int		len;
	char	c;

	len = 0;
	c = 0;
	while (*s && *s != ' ')
	{
		if (*s == '\'' || *s == '"')
		{
			c = *s;
			s++;
			while (*s && *s != c)
			{
				len++;
				s++;
			}
		}
		else
		{
			len++;
			s++;
		}
	}
	return (len);
}

static char			*create_word(char *s)
{
	char		*new;
	int			i;
	char		c;

	i = 0;
	c = 0;
	if (!(new = (char*)ft_memalloc(sizeof(char) * (get_len(s) + 1))))
		return (NULL);
	while (*s && *s != ' ')
	{
		if (*s == '\'' || *s == '"')
		{
			c = *s;
			s++;
			while (*s && *s != c)
				new[i++] = *(s++);
		}
		else
			new[i++] = *(s++);
	}
	new[i] = '\0';
	return (new);
}

char				**create_cmd(char *s)
{
	char		**tab;
	int			i;
	int			word;

	if (!s)
		return (NULL);
	i = 0;
	word = count_word(s);
	if (!(tab = (char**)malloc(sizeof(char*) * (word + 1))))
		return (NULL);
	while (word--)
	{
		while (*s && *s == ' ')
			s++;
		tab[i++] = create_word(s);
		s += get_len(s);
	}
	tab[i] = NULL;
	return (tab);
}
