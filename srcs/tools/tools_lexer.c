/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:48:18 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 18:15:47 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*jump_quote(char *cmd, char **new, int *i)
{
	char	c;

	c = *cmd;
	*new = ft_str_chr_cat(*new, *cmd);
	cmd++;
	(*i)++;
	while (*cmd && *cmd != c)
	{
		*new = ft_str_chr_cat(*new, *cmd);
		cmd++;
		(*i)++;
	}
	*new = ft_str_chr_cat(*new, *cmd);
	cmd++;
	(*i)++;
	return (cmd);
}

char		*jump_bs(char *cmd, char **new, int *i)
{
	*new = ft_str_chr_cat(*new, *cmd);
	cmd++;
	(*i)++;
	*new = ft_str_chr_cat(*new, *cmd);
	cmd++;
	(*i)++;
	return (cmd);
}

void		token_chevron(t_token **list, char *cmd)
{
	if (cmd	[0] == '>')
	{
		if (cmd[1] && cmd[1] == '>')
			add_token(list, new_token(">>", 3));
		else if (cmd[1] && cmd[1] == '&')
			add_token(list, new_token(">&", 3));
		else
			add_token(list, new_token(">", 3));
	}
	else if (cmd[0] == '<')
	{
		if (cmd[1] && cmd[1] == '<')
			add_token(list, new_token("<<", 3));
		else if (cmd[1] && cmd[1] == '&')
			add_token(list, new_token("<&", 3));
		else if (cmd[1] && cmd[1] == '>')
			add_token(list, new_token("<>", 3));
		else
			add_token(list, new_token("<", 3));
	}
}

int			check_chevron(t_token **list, char *cmd)
{
	int		i;
	char	c;

	i = 0;
	c = *cmd == '>' ? '>' : '<';
	if (cmd[1] && (cmd[1] == c || cmd[1] == '&'))
		i = 1;
	if (cmd[0] == '<' && cmd[1] && cmd[1] == '>')
		i = 1;
	token_chevron(list, cmd);
	return (i);
}

int			check_number(t_token **list, char *cmd)
{
	char	*new;

	new = NULL;
	if (*(cmd + 1) && (*(cmd + 1) == '>' || *(cmd + 1) == '<'))
	{
		new = ft_str_chr_cat(new, *cmd);
		add_token(list, new_token(new, 6));
		ft_strdel(&new);
		return (0);
	}
	return (add_word(cmd, list));
}
