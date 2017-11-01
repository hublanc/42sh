/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/31 17:11:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	compl_issigint(int n)
{
	t_cmd *cmd;

	if (n)
		;
	is_sigint(2);
	ft_putstr(tgetstr("cd", NULL));
	if ((cmd = save_cmd(NULL)))
		print_line(cmd);
	signal(SIGINT, &get_signal);
}

static char	*get_path(t_cmd *cmd)
{
	char	*word;
	int		i;

	if (!cmd->str)
		return (NULL);
	word = NULL;
	i = cmd->col - 1 - cmd->prlen;
	while (cmd->str[i] && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& cmd->str[i] != '\'' && (cmd->str[i] != ' '
			|| (i > 0 && cmd->str[i - 1] == '\\')) && (++i) > 0)
		go_right(cmd);
	i = cmd->col - 1 - cmd->prlen;
	if (i > 0 && (cmd->str[i] == '"' || cmd->str[i] == '\''
				|| cmd->str[i] == ' '))
		i--;
	while (i > 0 && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& (cmd->str[i] != ' ' || (i > 1 && cmd->str[i - 1] == '\\')))
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
	int	i;
	int	j;

	compl->path = get_path(cmd);
	i = -1;
	if (cmd->str && cmd->str[cmd->col - 2 - cmd->prlen] == '\\')
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		print_line(cmd);
		go_left(cmd);
	}
	j = ft_strlen(compl->path);
	while (compl->path && i < j && compl->path[++i])
		if (compl->path[i] == '\\' && i < j)
			ssupprchr(&(compl->path), i++);
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
	signal(SIGINT, &compl_issigint);
}

static void	reslash(t_compl *compl)
{
	char	*tmp;

	if (!compl || !compl->arg)
		return ;
	tmp = (compl->path && compl->path[ft_strlen(compl->path)] == '\\') ?
		ft_strjoin(add_handspace(compl->arg), "\\") : add_handspace(compl->arg);
	free(compl->arg);
	compl->arg = tmp;
}

void		completion(t_cmd *cmd, char ***env, char **buf)
{
	t_compl	compl;
	int		i;

	init_compl(&compl, cmd);
	list_compl(&compl, cmd, env, NULL);
	reslash(&compl);
	if (!compl.args.arg || compl_star(&compl, cmd))
	{
		ft_bzero(*buf, ft_strlen(*buf));
		return (compl_free(&compl));
	}
	(!compl.isslash && compl.path && compl.path[0]) ? add_line(cmd, "/") : 0;
	if ((i = 1) && !compl.args.next && compl.args.arg)
	{
		compl_addline(cmd, &compl);
		ft_bzero(*buf, ft_strlen(*buf));
		(compl.args.color && ft_strcmp("\e[1;36m", compl.args.color))
			? (*buf)[0] = ' ' : 0;
		return (compl_free(&compl));
	}
	display_args(&compl, cmd);
	while (i > 0)
		if ((i = compl_keys(&compl, cmd, buf)) == -1)
			ft_bzero(*buf, ft_strlen(*buf));
	compl_free(&compl);
}
