/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/02 12:02:59 by amazurie         ###   ########.fr       */
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

static void	check_bslash(t_compl *compl, t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	if (cmd->str && cmd->col - 2 - cmd->prlen >= 0
			&& cmd->str[cmd->col - 2 - cmd->prlen] == '\\')
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		print_line(cmd);
		go_left(cmd);
	}
	j = ft_strlen(compl->path);
	while (compl->path && i < j && compl->path[++i])
		if (compl->path[i] == '\\' && (compl->path[i + 1] == ' '
			|| compl->path[i + 1] == '\\'))
			ssupprchr(&(compl->path), i);
}

static void	init_compl(t_compl *compl, t_cmd *cmd)
{
	compl->path = get_path(cmd);
	check_bslash(compl, cmd);
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
	char	*tmp2;
	char	*tmp;

	if (!compl || !compl->arg)
		return ;
	if (compl->path && compl->path[ft_strlen(compl->path)] == '\\')
		tmp = ft_strjoin(add_handspace(compl->arg), "\\");
	else
	{
		tmp2 = add_handspace(compl->arg);
		tmp = add_backback(tmp2);
		free(tmp2);
	}
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
