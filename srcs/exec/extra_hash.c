/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 15:04:40 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/31 16:18:30 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_hash		**singleton_hash(void)
{
	static t_hash		*s_hash = NULL;

	return (&s_hash);
}

int			get_key(char *value)
{
	char		*tmp;
	int			res;

	res = 0;
	tmp = value;
	if (!value)
		return (-1);
	while (tmp && *tmp)
	{
		res += *tmp;
		tmp++;
	}
	return (res);
}

void		add_hash_table(char *path, char *value)
{
	t_hash		**list;

	list = singleton_hash();
	if (ft_strchr(value, '/') || !path || seek_value(value) != NULL)
		return ;
	*list = add_hash(*list, new_hash(value, path, get_key(value)));
}

t_hash		*seek_value(char *value)
{
	t_hash		**list;
	t_hash		*tmp;

	list = singleton_hash();
	tmp = *list;
	while (tmp && get_key(value) != tmp->key)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	while (tmp && ft_strcmp(tmp->value, value) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

int			is_in_htable(char *value, char **cmd)
{
	t_hash		*tmp;

	tmp = seek_value(value);
	if (!tmp)
		return (0);
	else if (tmp->path)
	{
		*cmd = ft_strdup(tmp->path);
		return (1);
	}
	return (0);
}
