/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:54:57 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 16:24:40 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_home(char **word, char ***env)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (env && *env && (*env)[i] && ft_strncmp("HOME=", (*env)[i], 5))
		i++;
	if (!env | !*env || !***env)
		i = -1;
	if (ft_strcmp(*word, "~") == 0)
	{
		free(*word);
		*word = NULL;
		if (i == -1)
			return ;
		*word = ft_strdup((*env)[i] + 5);
	}
	else if ((*word)[0] == '~' && (*word)[1] == '/')
	{
		tmp = ft_strdup(*word + 1);
		free(*word);
		*word = NULL;
		if (i == -1)
			return ;
		tmp2 = ft_strdup((*env)[i] + 5);
		if (!tmp2)
			tmp = "~";
		*word = ft_strjoin(tmp2, tmp);
		free(tmp2);
		free(tmp);
	}
}

static char	*get_path(t_cmd *cmd, char ***env)
{
	char	*word;
	int		i;

	if (!cmd->str)
		return (NULL);
	i = cmd->col - 1 - cmd->prlen;
	while (cmd->str[i] && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& cmd->str[i] != '\'' && cmd->str[i] != ' ')
	{
		go_right(cmd);
		i = cmd->col - 1 - cmd->prlen;
	}
	i = cmd->col - 1 - cmd->prlen;
	while (i > 0 && cmd->str[i] != '"' && cmd->str[i] != '\''
			&& cmd->str[i] != ' ')
		i--;
	if (cmd->str[i] == '"' || cmd->str[i] == '\'' || cmd->str[i] == ' ')
		i++;
	while (cmd->str[i] == ' ')
		i++;
	if (i > cmd->col - 1 - cmd->prlen)
		return (NULL);
	word = ft_strndup(cmd->str + i, cmd->col - 1 - cmd->prlen - i);
	check_home(&word, env);
	return (word);
}

int			completion(t_cmd *cmd, char ***env, char **buf)
{
	t_compl	compl;
	char	*path;
	int		i;

	path = get_path(cmd, env);
	// futur arg = get_arg(path);
	compl.arg = path;
	list_compl(&compl, env);
	i = 1;
	compl.curr = 0;
	compl.toskip = 0;
	if (!compl.args.next)
		add_line(cmd, compl.args.arg + ft_strlen(compl.arg));
	else
	{
		display_args(&compl, cmd);
		while (i > 0)
			if ((i = compl_keys(&compl, cmd, buf)) == -1)
				ft_bzero(*buf, ft_strlen(*buf));
	}
	if (path)
		free(path);
	return (0);
}
