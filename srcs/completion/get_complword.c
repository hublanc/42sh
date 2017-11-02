/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/31 17:11:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*check_complhome(t_cmd *cmd, char **word,  int i)
{
	while (cmd->str[i] == ' ')
		i++;
	if (i > cmd->col - 1 - cmd->prlen)
		return (NULL);
	*word = ft_strndup(cmd->str + i, cmd->col - 1 - cmd->prlen - i);
	return (*word);
}

char		*get_path(t_cmd *cmd)
{
	char	*word;
	int		i;

	if (!cmd->str)
		return (NULL);
	word = NULL;
	i = cmd->col - 1 - cmd->prlen;
	while (cmd->str[i] && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& cmd->str[i] != '\'' && (cmd->str[i] != ' '
			|| (i > 0 && cmd->str[i - 1] == '\\')) && (++i) > 0)
		go_right(cmd);
	i = cmd->col - 1 - cmd->prlen;
	if (i > 0 && (cmd->str[i] == '"' || cmd->str[i] == '\''
				|| cmd->str[i] == ' '))
		i--;
	while (i > 0 && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& (cmd->str[i] != ' ' || (i > 1 && cmd->str[i - 1] == '\\')))
		i--;
	if (cmd->str[i] == '"' || cmd->str[i] == '\'' || cmd->str[i] == ' ')
		i++;
	return (check_complhome(cmd, &word, i));
}
