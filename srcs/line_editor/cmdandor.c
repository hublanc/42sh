/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:49:51 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 17:03:33 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			check_cmdandor(char *cmd)
{
	char	*str;

	str = cmd;
	while (str && *str)
	{
		if (*str && *str == '&' && *(str + 1) == '&')
		{
			str += 2;
			while (*str && *str == ' ')
				str++;
			if (*str == '\0')
				return (0);
		}
		else if (*str && *str == '|' && *(str + 1) == '|')
		{
			str += 2;
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

void		enter_handler_cmdandor(t_cmd *cmd, t_control **history)
{
	char	c;

	cmd->str_quote = ft_strapp(cmd->str_quote, cmd->str);
	ft_strdel(&(cmd->str));
	if (ttyyyy(2))
		!ttyyyy(0) ? ft_putchar_fd('\n', 2) : ft_putchar('\n');
	c = check_quote(cmd->str_quote);
	if (c == '\\')
		prompt_backslash(cmd, history, 1);
	else if (c == '\'' || c == '"')
		prompt_quote(cmd, history, c, 1);
	if (!checkstr_pipe(cmd->str_quote))
		prompt_pipe(cmd, history, 1);
	if (!check_cmdandor(cmd->str_quote))
	{
		ttyyyy(2) ? ft_putstr_fd(cmd->prompt, 2) : 0;
		cmd->col = cmd->prlen + 1;
		cmd->str_quote = ft_strapp(cmd->str_quote, " ");
	}
}

void		prompt_cmdandor(t_cmd *cmd, t_control **history, int mod)
{
	t_cmd		cmd_ao;

	cmd_ao = init_cmd("cmdandor> ");
	ttyyyy(2) ? ft_putstr_fd(cmd_ao.prompt, 2) : 0;
	if (!mod)
		cmd_ao.str_quote = ft_strapp(cmd_ao.str_quote, cmd->str);
	else if (mod)
		cmd_ao.str_quote = ft_strapp(cmd_ao.str_quote, cmd->str_quote);
	while (!check_cmdandor(cmd_ao.str_quote) && !cmd_ao.stop)
		key_handler(&cmd_ao, history, NULL);
	if (!mod)
	{
		cmd->str ? ft_strdel(&(cmd->str)) : 0;
		cmd->str = ft_strdup(cmd_ao.str_quote);
	}
	if (mod)
	{
		cmd->str_quote ? ft_strdel(&(cmd->str_quote)) : 0;
		cmd->str_quote = ft_strdup(cmd_ao.str_quote);
	}
	clear_cmd(&cmd_ao);
	save_cmd(cmd);
}
