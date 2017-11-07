/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:57:56 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 17:33:11 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		add_hist_or_not(t_control **history, char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = NULL;
	if (!str)
		return ;
	cpy = ft_strdup(str);
	while (ft_strchr(cpy, '\n'))
	{
		i = ft_strchr(cpy, '\n') - cpy;
		cpy[i] = ' ';
	}
	if (*history && (*history)->begin && (*history)->begin->name
			&& ft_strcmp((*history)->begin->name, cpy) == 0)
	{
		ft_strdel(&cpy);
		return ;
	}
	else
		(*history) = dll_add_new_elem_frnt(*history, cpy);
	ft_strdel(&cpy);
}

void		change_cmd(char *new, t_cmd *cmd)
{
	go_begin(cmd->col, cmd->sc_col);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	if (!ft_strcmp(cmd->prompt, "dquote> ")
		|| !ft_strcmp(cmd->prompt, "quote> ")
		|| !ft_strcmp(cmd->prompt, "heredoc> ")
		|| !ft_strcmp(cmd->prompt, "pipe> "))
		ft_putstr_fd(cmd->prompt, 2);
	else
		print_prompt();
	ft_putstr_fd(new, 2);
	cmd->col = ft_strlen(new) + cmd->prlen + (cmd->prlen ? 1 : 0);
	ft_strdel(&(cmd->str));
	cmd->str = ft_strdup(new);
	if (cmd->col % cmd->sc_col == 1)
	{
		tputs(tgetstr("cr", NULL), 1, tputchar);
		tputs(tgetstr("do", NULL), 1, tputchar);
	}
}

void		set_selected_null(t_control **history)
{
	t_lst		*tmp;

	if ((*history) == NULL)
		return ;
	tmp = NULL;
	tmp = (*history)->begin;
	while (tmp != NULL)
	{
		tmp->selected = 0;
		tmp = tmp->next;
	}
}

int			return_void(t_cmd *cmd, t_control **history, char ***env)
{
	if (history_search(history, &cmd->str) == 1)
		enter_hub(cmd, history, env);
	else
		print_prompt();
	return (1);
}

void		delete_elem(t_lst **tmp)
{
	if (*tmp && (*tmp)->name)
		ft_strdel(&(*tmp)->name);
	if (*tmp)
		free(*tmp);
}
