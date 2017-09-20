/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 13:51:51 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_path(t_cmd *cmd)
{
	char	*arg;
	int		i;
	int		j;

	if (!cmd->str)
		return (NULL);
	j = cmd->col - cmd->prlen - 1;
	while ((ft_isalnum(cmd->str[j]) || cmd->str[j] == '/') && cmd->str[j] != ' ')
		j++;
	i = cmd->col - cmd->prlen - 2;
	(i < 0) ? i = 0 : 0;
	while (i > 0 && (ft_isalnum(cmd->str[i]) || cmd->str[i] == '/') && cmd->str[i] != ' ')
		i--;
	(cmd->str[i] == ' ') ? i++ : 0;
	arg = ft_strndup(cmd->str + i, j - i);
	i = cmd->col - cmd->prlen;
	while (j-- - i + 1 > 0)
		go_right(cmd);
	return (arg);
}

int			completion(t_cmd *cmd, char ***env, char **buf)
{
	t_compl	compl;
	char	*path;
	int		i;

	path = get_path(cmd);
	// futur arg = get_arg(path);
	compl.arg = path;
	list_compl(&compl, env);
	i = 1;
	compl.curr = 0;
	if (!compl.args.next)
		add_line(cmd, compl.args.arg + ft_strlen(compl.arg));
	else
	{
		display_args(&compl, cmd);
		while (i > 0)
			if ((i = compl_keys(&compl, cmd, buf)) == -1)
				ft_bzero(*buf, ft_strlen(*buf));
	}
	if (path)
		free(path);
	return (0);
}
