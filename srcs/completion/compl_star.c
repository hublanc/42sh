/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:09:06 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/23 11:57:35 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	prep_complstar2(t_compl *compl, t_cmd *cmd)
{
	int			i;

	if (compl->path[ft_strlen(compl->path) - 1] == '/')
		compl->path[ft_strlen(compl->path) - 1] = 0;
	if (!compl->isslash)
	{
		cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
		go_left(cmd);
	}
	i = ft_strlen(compl->arg);
	while (i--)
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		go_left(cmd);
	}
}

static void	prep_complstar(t_compl *compl, t_cmd *cmd)
{
	cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
	go_left(cmd);
	if (compl->arg && compl->arg[0] && compl->isstar > 1)
	{
		while (compl->arg[ft_strlen(compl->arg - 1)] ==
				cmd->str[cmd->col - 1 - cmd->prlen])
		{
			cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
			go_left(cmd);
		}
		if (cmd->str[cmd->col - 1 - cmd->prlen] == '/')
		{
			cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
			go_left(cmd);
		}
	}
}

static int	compl_star2(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*ar;
	char		*tmp;
	char		*tmp2;

	prep_complstar2(compl, cmd);
	ar = &compl->args;
	tmp = ft_strjoin(ar->arg, " ");
	while (ar && (ar = ar->next) && ar->arg)
	{
		tmp2 = ft_strjoin(tmp, compl->path);
		(tmp) ? free(tmp) : 0;
		tmp = ft_strjoin(tmp2, "/");
		(tmp2) ? free(tmp2) : 0;
		tmp2 = ft_strjoin(tmp, ar->arg);
		(tmp) ? free(tmp) : 0;
		tmp = ft_strjoin(tmp2, " ");
		(tmp2) ? free(tmp2) : 0;
	}
	if ((size_t)(cmd->col - 1 - cmd->prlen) > ft_strlen(cmd->str))
		go_left(cmd);
	add_line(cmd, tmp);
	free(tmp);
	return (1);
}

int			compl_star(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*ar;
	char		*tmp;
	char		*tmp2;

	if (!compl->isstar)
		return (0);
	if (!compl->path && compl->arg)
		return (1);
	prep_complstar(compl, cmd);
	if (compl->isstar == 2 || (compl->isstar == 3 && compl->path))
		return (compl_star2(compl, cmd));
	ar = &compl->args;
	tmp = ft_strjoin(ar->arg, " ");
	while (ar && (ar = ar->next) && ar->arg)
	{
		tmp2 = ft_strjoin(tmp, ar->arg);
		(tmp) ? free(tmp) : 0;
		tmp = ft_strjoin(tmp2, " ");
		(tmp2) ? free(tmp2) : 0;
	}
	add_line(cmd, tmp);
	(tmp) ? free(tmp) : 0;
	return (1);
}
