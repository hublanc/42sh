/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:21:04 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/17 15:04:02 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		check_quote(char *str)
{
	char	in_quote;
	int		ignore;

	ignore = 0;
	in_quote = 0;
	while (str && *str)
	{
		ft_putchar(*str);
		ft_putendl("");
		if (*str == '\\' && (!in_quote || (in_quote == '"'
			&& *(str + 1) && *(str + 1) == '"')))
		{
			if (*(str + 1))
				str += (in_quote == '"' && *(str + 1) == '"') ? 2 : 1;
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

void		prompt_quote(t_cmd *cmd, t_control **history, char c, int mod)
{
	t_cmd		cmd_q;

	cmd_q = (c == '"') ? init_cmd("dquote> ") : init_cmd("quote> ");
	save_cmd(&cmd_q);
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
		(cmd->str) ? ft_strdel(&(cmd->str)) : 0;
		cmd->str = ft_strdup(cmd_q.str_quote);
	}
	else if (mod)
	{
		cmd->str_quote ? ft_strdel(&(cmd->str_quote)) : 0;
		cmd->str_quote = ft_strdup(cmd_q.str_quote);
	}
	clear_cmd(&cmd_q);
	save_cmd(cmd);
}

void		prompt_backslash(t_cmd *cmd, t_control **history, int mod)
{
	t_cmd		cmd_b;

	cmd_b = init_cmd("> ");
	save_cmd(&cmd_b);
	ft_putstr_fd(cmd_b.prompt, 2);
	if (!mod)
		cmd_b.str_quote = ft_strapp(cmd_b.str_quote, cmd->str);
	else if (mod)
		cmd_b.str_quote = ft_strapp(cmd_b.str_quote, cmd->str_quote);
	cmd_b.str_quote = ft_strdelone(cmd_b.str_quote,
					(int)ft_strlen(cmd_b.str_quote));
	while (!(cmd_b.end_bs) && !cmd_b.stop)
		key_handler(&cmd_b, history, NULL);
	if (!mod)
	{
		cmd->str ? ft_strdel(&(cmd->str)) : 0;
		cmd->str = ft_strdup(cmd_b.str_quote);
	}
	else if (mod)
	{
		cmd->str ? ft_strdel(&(cmd->str_quote)) : 0;
		cmd->str_quote = ft_strdup(cmd_b.str_quote);
	}
	clear_cmd(&cmd_b);
	save_cmd(cmd);
}
