/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 16:24:40 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_path(t_cmd *cmd)
{
	char	*word;
	int		i;

	if (!cmd->str)
		return (NULL);
	i = cmd->col - 1 - cmd->prlen;
	while (cmd->str[i] && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& cmd->str[i] != '\'' && cmd->str[i] != ' ')
	{
		go_right(cmd);
		i++;
	}
	i = cmd->col - 1 - cmd->prlen;
	if (i > 0 && (cmd->str[i] == '"' || cmd->str[i] == '\'' || cmd->str[i] == ' '))
		i--;
	while (i > 0 && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& cmd->str[i] != ' ')
		i--;
	if (cmd->str[i] == '"' || cmd->str[i] == '\'' || cmd->str[i] == ' ')
		i++;
	while (cmd->str[i] == ' ')
		i++;
	if (i > cmd->col - 1 - cmd->prlen)
		return (NULL);
	word = ft_strndup(cmd->str + i, cmd->col - 1 - cmd->prlen - i);
	return (word);
}

void		completion(t_cmd *cmd, char ***env, char **buf)
{
	t_compl	compl;
	int		i;

	compl.path = get_path(cmd);
	compl.arg = ft_strdup(compl.path);
	list_compl(&compl, cmd, env);
	i = 1;
	compl.ar = NULL;
	compl.curr = -1;
	compl.toskip = 0;
	if (!compl.args.arg || compl_star(&compl, cmd))
	{
		ft_bzero(*buf, ft_strlen(*buf));
		return ;
	}
	if (!compl.isslash && compl.path && compl.path[0])
		add_line(cmd, "/");
	if (!compl.args.next && compl.args.arg)
	{
		add_line(cmd, compl.args.arg + ft_strlen(compl.arg));
		ft_bzero(*buf, ft_strlen(*buf));
		(*buf)[0] = ' ';
		return ;
	}
	else
	{
		display_args(&compl, cmd);
		while (i > 0)
			if ((i = compl_keys(&compl, cmd, buf)) == -1)
				ft_bzero(*buf, ft_strlen(*buf));
	}
}
