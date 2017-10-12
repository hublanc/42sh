/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdandor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 13:49:51 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/28 19:00:54 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			check_cmdandor(char *cmd)
{
	char	*str;

	str = cmd;
	while (*str)
	{
		if (*str && *str == '&' && *(str + 1) == '&')
		{
			str += 2;
			if (*str == '\0')
				return (0);
		}
		else if (*str && *str == '|' && *(str + 1) == '|')
		{
			str += 2;
			if (*str == '\0')
				return (0);
		}
		else
			str++;
	}
	return (1);
}

void		enter_handler_cmdandor(t_cmd *cmd, t_hist **history)
{
	char	c;

	cmd->str_quote = ft_strapp(cmd->str_quote, cmd->str);
	ft_strdel(&(cmd->str));
	ft_putchar('\n');
	c = check_quote(cmd->str_quote);
	if (!c)
		return ;
	else if (c == '\\')
		prompt_backslash(cmd, history, 1);
	else if (c == '\'' || c == '"')
		prompt_quote(cmd, history, c, 1);
}

void		prompt_cmdandor(t_cmd *cmd, t_hist **history, int mod)
{
	t_cmd		cmd_ao;

	cmd_ao = init_cmd("cmdandor> ");
	ft_putstr(cmd_ao.prompt);
	if (!mod)
		cmd_ao.str_quote = ft_strapp(cmd_ao.str_quote, cmd->str);
	else if (mod)
		cmd_ao.str_quote = ft_strapp(cmd_ao.str_quote, cmd->str_quote);
	while (!check_cmdandor(cmd_ao.str_quote))
		key_handler(&cmd_ao, history, NULL);
	if (!mod)
	{
		ft_strdel(&(cmd->str));
		cmd->str = ft_strdup(cmd_ao.str_quote);
	}
	if (mod)
	{
		ft_strdel(&(cmd->str_quote));
		cmd->str_quote = ft_strdup(cmd_ao.str_quote);
	}
	clear_cmd(&cmd_ao);
}
