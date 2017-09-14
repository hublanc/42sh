/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 17:55:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:50:09 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		print_line_pipe(t_cmd *cmd)
{
	int		len;

	len = cmd->prlen + (int)ft_strlen(cmd->str);
	len += len % cmd->sc_col == 0 ? 0 : 1;
	go_begin(cmd->col, cmd->sc_col);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr(cmd->prompt);
	ft_putstr(cmd->str);
	if (len > cmd->col)
	{
		while (len-- != cmd->col)
			tputs(tgetstr("le", NULL), 1, tputchar);
	}
	else if (len < cmd->col)
	{
		while (len != cmd->col)
		{
			if (len % cmd->sc_col == 0)
				tputs(tgetstr("do", NULL), 1, tputchar);
			else
				tputs(tgetstr("nd", NULL), 1, tputchar);
			len++;
		}
	}
}

int		enter_handler_pipe(t_cmd *cmd, t_token **list, t_token *new)
{
	t_token		*tmp;

	tmp = NULL;
	ft_putchar('\n');
	if (!cmd->str)
	{
		ft_putstr(cmd->prompt);
		return (0);
	}
	if (check_quote(cmd->str))
		prompt_quote(cmd, NULL, '"', 0);
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

int		key_handler_pipe(t_cmd *cmd, t_token **list, t_token *new)
{
	char	buf[6];

	init_screen(cmd);
	bzero(buf, 6);
	read(0, buf, 5);
	if (buf[0] == 27)
		arrow_handler(buf, cmd, NULL);
	else if (buf[0] == 127 && cmd->col > cmd->prlen)
	{
		cmd->str = ft_strdelone(cmd->str, cmd->col - cmd->prlen - 1);
		print_line_pipe(cmd);
		go_left(cmd);
	}
	else if (buf[0] == 10)
		return (enter_handler_pipe(cmd, list, new));
	else if (ft_isprint(buf[0]))
	{
		cmd->str = ft_strappone(cmd->str, buf[0], cmd->col - cmd->prlen - 1);
		print_line_pipe(cmd);
		go_right(cmd);
	}
	return (0);
}

t_token	*prompt_pipe(t_token *list)
{
	t_cmd		cmd_p;
	t_token		*new;

	new = NULL;
	cmd_p = init_cmd("pipe> ");
	ft_putstr("pipe> ");
	while (!key_handler_pipe(&cmd_p, &list, new));
	return (list);
}
