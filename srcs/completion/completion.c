/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/28 15:09:10 by amazurie         ###   ########.fr       */
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
			&& cmd->str[i] != '\'' && cmd->str[i] != ' ' && (++i) > 0)
		go_right(cmd);
	i = cmd->col - 1 - cmd->prlen;
	if (i > 0 && (cmd->str[i] == '"' || cmd->str[i] == '\''
				|| cmd->str[i] == ' '))
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

static void	init_compl(t_compl *compl, t_cmd *cmd)
{
	compl->path = get_path(cmd);
	compl->arg = ft_strdup(compl->path);
	compl->args.next = NULL;
	compl->args.arg = NULL;
	compl->isstar = 0;
	compl->bi = 1;
	compl->maxlen = 0;
	compl->nbrargs = 0;
	compl->isdot = 0;
	compl->isslash = 0;
	compl->ar = NULL;
	compl->curr = -1;
	compl->toskip = 0;
}

void		completion(t_cmd *cmd, char ***env, char **buf)
{
	t_compl	compl;
	int		i;

	init_compl(&compl, cmd);
	list_compl(&compl, cmd, env);
	i = 1;
	if (!compl.args.arg || compl_star(&compl, cmd))
	{
		ft_bzero(*buf, ft_strlen(*buf));
		return compl_free(&compl);
	}
	if (!compl.isslash && compl.path && compl.path[0])
		add_line(cmd, "/");
	if (!compl.args.next && compl.args.arg)
	{
		add_line(cmd, compl.args.arg + ft_strlen(compl.arg));
		ft_bzero(*buf, ft_strlen(*buf));
		(*buf)[0] = ' ';
		return compl_free(&compl);
	}
	display_args(&compl, cmd);
	while (i > 0)
		if ((i = compl_keys(&compl, cmd, buf)) == -1)
			ft_bzero(*buf, ft_strlen(*buf));
	compl_free(&compl);
}
