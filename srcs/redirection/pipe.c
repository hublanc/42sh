/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 17:55:21 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 16:59:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*extra_checkstr_pipe(char *str)
{
	str += 2;
	while (*str || *str == ' ' || *str == '\n' || *str == '\t')
		str++;
	return (str);
}

int				checkstr_pipe(char *cmd)
{
	char		*str;

	str = cmd;
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '|' && *(str + 1) && *(str + 1) == '|')
		{
			str = extra_checkstr_pipe(str);
			if (*str == '|')
				return (1);
		}
		else if (*str == '|')
		{
			str++;
			while (*str && *str == ' ')
				str++;
			if (*str == '\0')
				return (0);
		}
		else
			str++;
	}
	return (1);
}

void			enter_handler_pipe(t_cmd *cmd, t_control **history)
{
	char	c;

	cmd->str_quote = ft_strapp(cmd->str_quote, cmd->str);
	ft_strdel(&(cmd->str));
	if (ttyyyy(2))
		!ttyyyy(0) ? ft_putchar_fd('\n', 2) :  ft_putchar('\n');
	c = check_quote(cmd->str_quote);
	if (c == '\\')
		prompt_backslash(cmd, history, 1);
	else if (c == '\'' || c == '"')
		prompt_quote(cmd, history, c, 1);
	if (!check_cmdandor(cmd->str_quote))
		prompt_cmdandor(cmd, history, 1);
	if (!checkstr_pipe(cmd->str_quote))
	{
		ttyyyy(0) ? ft_putstr(cmd->prompt) : 0;
		cmd->col = cmd->prlen + 1;
		cmd->str_quote = ft_strapp(cmd->str_quote, " ");
	}
}

void			prompt_pipe(t_cmd *cmd, t_control **history, int mod)
{
	t_cmd		cmd_p;

	cmd_p = init_cmd("pipe> ");
	ttyyyy(0) ? ft_putstr("pipe> ") : 0;
	if (!mod)
		cmd_p.str_quote = ft_strapp(cmd_p.str_quote, cmd->str);
	else if (mod)
		cmd_p.str_quote = ft_strapp(cmd_p.str_quote, cmd->str_quote);
	while (!checkstr_pipe(cmd_p.str_quote) && !cmd_p.stop)
		key_handler(&cmd_p, history, NULL);
	if (!mod)
	{
		cmd->str ? ft_strdel(&(cmd->str)) : 0;
		cmd->str = ft_strdup(cmd_p.str_quote);
	}
	if (mod)
	{
		cmd->str_quote ? ft_strdel(&(cmd->str_quote)) : 0;
		cmd->str_quote = ft_strdup(cmd_p.str_quote);
	}
	clear_cmd(&cmd_p);
	save_cmd(cmd);
}
