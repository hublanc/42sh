/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 12:54:29 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_arg(t_cmd *cmd)
{
	char	*arg;
	int		i;
	int		j;

	if (!cmd->str)
		return (NULL);
	j = cmd->col - cmd->prlen - 1;
	while (ft_isalnum(cmd->str[j]) || cmd->str[j] == '/')
		j++;
	i = cmd->col - cmd->prlen - 2;
	(i < 0) ? i = 0 : 0;
	while (i > 0 && (ft_isalnum(cmd->str[i]) || cmd->str[i] == '/'))
		i--;
	arg = ft_strndup(cmd->str + i, j - i);
	return (arg);
}

int			completion(t_cmd *cmd, char ***env)
{
	t_compl	compl;
	char	*arg;
//	char	*path;
//
//	path = get_path(cmd);
	arg = get_arg(cmd);
	list_compl(&compl, arg, env);
	if (arg)
		free(arg);
	return (0);
}
