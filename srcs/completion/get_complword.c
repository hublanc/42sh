/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_complword.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 10:12:17 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/02 12:16:21 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*check_complhome(t_cmd *cmd, char **word, int i)
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

static void	compl_cmpdol(t_compl *compl, char **word)
{
	int	i;

	if (!word || !*word || !(*word)[0])
		return ;
	i = ft_strlen(*word) - 1;
	while (i > 0 && ((*word)[i] != '$' || (*word)[i - 1] == '\\'))
		i--;
	if (i <= 0)
		return ;
	if (!compl->isdot && i > 0 && (compl->isslash = 1))
	{
		ft_memmove(*word, *word + i, ft_strlen(*word + i));
		ft_bzero(*word + ft_strlen(*word) - i, i);
	}
}

void		compl_cmp(t_compl *compl, char **word)
{
	int	i;

	if (!*word || !(*word)[0] || !compl->path || ft_strncmp(compl->path, *word,
				ft_strlen(compl->path)) || (*word)[0] != compl->path[0])
		return (compl_cmpdol(compl, word));
	if ((*word)[0] == '.' && (!(*word)[1] || ((*word)[1] != '.'
					&& (*word)[1] != '/')))
		compl->isdot = 1;
	if (compl->isdot || (*word)[ft_strlen(*word) - 1] == '/')
		compl->isslash = 1;
	compl->isstar = (compl->isstar == 3) ? 2 : 0;
	i = ft_strlen(*word) - 1;
	while (i > 0 && ((*word)[i] != '/' || (*word)[i - 1] == '\\'))
		i--;
	((*word)[i] == '/') ? i++ : 0;
	if (!(*word)[i] || (!compl->isdot && i <= 0))
	{
		free(*word);
		*word = NULL;
	}
	else if (!compl->isdot && i > 0 && (compl->isslash = 1))
	{
		ft_memmove(*word, *word + i, ft_strlen(*word + i));
		ft_bzero(*word + ft_strlen(*word) - i, i);
	}
}
