/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 12:22:12 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 12:32:44 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			*add_fd(int *fds, t_node *tree, char ***env)
{
	int		*new;
	int		i;

	i = 0;
	if (!fds)
	{
		new = (int*)ft_memalloc(sizeof(int) * 2);
		new[0] = open_file(tree, env);
		new[1] = -1;
		return (new);
	}
	while (fds[i] != -1)
		i++;
	new = (int*)ft_memalloc(sizeof(int) * (i + 2));
	i = 0;
	while (fds[i] != -1)
	{
		new[i] = fds[i];
		i++;
	}
	new[i++] = open_file(tree, env);
	new[i] = -1;
	ft_memdel((void**)&fds);
	return (new);
}

int			*add_io(int *fds, t_node *tree, int io)
{
	int		*new;
	int		i;

	i = 0;
	if (!fds)
	{
		new = (int*)ft_memalloc(sizeof(int) * 2);
		new[0] = ft_isdigit((tree->token[0])) ? ft_atoi(tree->token) : io;
		new[1] = -1;
		return (new);
	}
	while (fds[i] != -1)
		i++;
	new = (int*)ft_memalloc(sizeof(int) * (i + 2));
	i = 0;
	while (fds[i] != -1)
	{
		new[i] = fds[i];
		i++;
	}
	new[i++] = ft_isdigit((tree->token[0])) ? ft_atoi(tree->token) : io;
	new[i] = -1;
	ft_memdel((void**)&fds);
	i = 0;
	return (new);
}

char		**add_w(char **tab, t_node *tree, int cut)
{
	char	**new;
	int		i;

	i = 0;
	if (!tab)
	{
		new = (char**)ft_memalloc(sizeof(char*) * 2);
		new[0] = ft_strsub(tree->token, cut, ft_strlen(tree->token) - cut);
		new[1] = NULL;
		return (new);
	}
	new = (char**)ft_memalloc(sizeof(char*) * (len_array(tab) + 1));
	while (tab[i])
	{
		new[i] = tab[i];
		i++;
	}
	new[i++] = ft_strsub(tree->token, cut, ft_strlen(tree->token) - cut);
	new[i] = NULL;
	del_tabstr(&tab);
	return (new);
}
