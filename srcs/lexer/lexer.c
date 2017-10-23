/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 17:54:51 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/23 13:16:57 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				isspecial(char c)
{
	if (c == ';' || c == '|' || c == '&' || c == '<' || c == '>' || c == ' ')
		return (0);
	else
		return (1);
}

int				add_word(char *cmd, t_token **list)
{
	char		*new;
	int			i;

	i = 0;
	new = NULL;
	if (!cmd)
		return (0);
	while (*cmd && isspecial(*cmd))
	{
		if (*cmd == '\'' || *cmd == '"')
			cmd = jump_quote(cmd, &new, &i);
		else if (*cmd == '\\')
			cmd = jump_bs(cmd, &new, &i);
		else
		{
			new = ft_str_chr_cat(new, *cmd);
			cmd++;
			i++;
		}
	}
	add_token(list, new_token(new, 1));
	ft_strdel(&new);
	return (i - 1);
}

int				add_pipe_or_word(char *cmd, t_token **list)
{
	int		i;

	i = 0;
	if (*(cmd + 1) && *(cmd + 1) == '|')
	{
		add_token(list, new_token("||", 8));
		i++;
	}
	else
		add_token(list, new_token("|", 4));
	return (i);
}

void			check_type(char **cmd, t_token **list)
{
	int		i;

	i = 1;
	if (!cmd || !*cmd || !**cmd)
		return ;
	if (**cmd == ';')
		add_token(list, new_token(";", 5));
	else if (**cmd == '|')
		i += add_pipe_or_word(*cmd, list);
	else if (**cmd == '&')
	{
		(!*(*cmd + 1) || *(*cmd + 1) != '&') ?
			*list = abort_sort(*list, "&") : add_token(list, new_token("&&", 7));
		i++;
	}
	else if (**cmd == '<' || **cmd == '>')
		i += check_chevron(list, *cmd);
	else if (ft_isdigit(**cmd))
		i += check_number(list, *cmd);
	else
		i += add_word(*cmd, list);
	while (i-- > 0 && **cmd)
		(*cmd)++;
}

t_token			*tokenizer(char *cmd)
{
	t_token	*list;

	list = NULL;
	if (!cmd)
		return (NULL);
	while (*cmd)
	{
		while (*cmd && *cmd == 32)
			cmd++;
		check_type(&cmd, &list);
	}
	return (list);
}
