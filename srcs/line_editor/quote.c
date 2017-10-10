/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:21:04 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/29 15:11:18 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		check_quote(char *str)
{
	char	in_quote;
	int		ignore;

	in_quote = 0;
	ignore = 0;
	while (str && *str)
	{
		if (*str == '\\' && !in_quote)
		{
			if (*(str + 1))
				str += 2;
			else
				return ('\\');
		}
		else
		{
			if (in_quote == *str)
				in_quote = 0;
			else if (!in_quote && (*str == '\'' || *str == '"'))
				in_quote = *str;
		}
		str++;
	}
	return (in_quote);
}

void		prompt_quote(t_cmd *cmd, t_hist **history, char c, int mod)
{
	t_cmd		cmd_q;

	if (c == '"')
		cmd_q = init_cmd("dquote> ");
	else
		cmd_q = init_cmd("quote> ");
	ft_putstr(cmd_q.prompt);
	if (!mod)
		cmd_q.str_quote = ft_strapp(cmd_q.str_quote, cmd->str);
	else if (mod)
		cmd_q.str_quote = ft_strapp(cmd_q.str_quote, cmd->str_quote);
	cmd_q.str_quote = ft_strapp(cmd_q.str_quote, "\n");
	while (check_quote(cmd_q.str_quote) && !cmd_q.stop)
		key_handler(&cmd_q, history, NULL);
	if (!mod)
	{
		ft_strdel(&(cmd->str));
		cmd->str = ft_strdup(cmd_q.str_quote);
	}
	else if (mod)
	{
		ft_strdel(&(cmd->str_quote));
		cmd->str_quote = ft_strdup(cmd_q.str_quote);
	}
	clear_cmd(&cmd_q);
}

void		prompt_backslash(t_cmd *cmd, t_hist **history, int mod)
{
	t_cmd		cmd_b;

	cmd_b = init_cmd("> ");
	ft_putstr(cmd_b.prompt);
	if (!mod)
		cmd_b.str_quote = ft_strapp(cmd_b.str_quote, cmd->str);
	else if (mod)
		cmd_b.str_quote = ft_strapp(cmd_b.str_quote, cmd->str_quote);
	cmd_b.str_quote = ft_strdelone(cmd_b.str_quote, (int)ft_strlen(cmd_b.str_quote));
	while (!(cmd_b.end_bs) && !cmd_b.stop)
		key_handler(&cmd_b, history, NULL);
	if (!mod)
	{
		ft_strdel(&(cmd->str));
		cmd->str = ft_strdup(cmd_b.str_quote);
	}
	else if (mod)
	{
		ft_strdel(&(cmd->str_quote));
		cmd->str_quote = ft_strdup(cmd_b.str_quote);
	}
	clear_cmd(&cmd_b);
}
