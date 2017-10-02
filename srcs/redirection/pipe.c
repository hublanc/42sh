/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 17:55:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/02 13:15:26 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		check_enter_pipe(t_cmd *cmd, t_token **list, t_token *new)
{
	t_token		*tmp;

	tmp = NULL;
	new = tokenizer(cmd->str);
	tmp = new;
	while (tmp)
	{
		add_token(list, new_token(tmp->token, tmp->e_type));
		tmp = tmp->next;
	}
	del_token(&new);
	ft_strdel(&(cmd->str_quote));
	return (1);
}

int		prompt_pipe(t_token *list, t_hist **history)
{
	t_cmd		cmd_p;
	t_token		*new;

	new = NULL;
	cmd_p = init_cmd("pipe> ");
	ft_putstr(cmd_p.prompt);
	while (!cmd_p.end_pp && !cmd_p.stop)
		key_handler(&cmd_p, history, NULL);
	(!cmd_p.stop) ? check_enter_pipe(&cmd_p, &list, new) : 0;
	return ((!cmd_p.stop) ? 1 : 0);
}
