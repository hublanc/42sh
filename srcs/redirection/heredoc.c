/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:56:32 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/01 17:10:10 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		*singleton_ioheredoc(void)
{
	static int		s_iohere = 0;

	return (&s_iohere);
}

void	heredoc_input(t_node *tree)
{
	exec_dup(tree->hd, tree->hd_io);
	close(tree->hd);
}

void			manage_heredoc(t_node *tree, t_node *tmp)
{
	int		i;
	int		fd[2];
	int		*io;

	i = len_io(tree->token);
	io = singleton_ioheredoc();
	pipe(fd);
	if (tmp->heredoc_str)
		ft_strdel(&(tmp->heredoc_str));
	tmp->heredoc_str = ft_strsub(tree->token, i + 3,
			ft_strlen(tree->token) - (i + 3));
	ft_putstr_fd(tmp->heredoc_str, fd[1]);
	close(fd[1]);
	tmp->hd = fd[0];
	tmp->hd_io = *io;
}

static char		*eof_quote(char *str, int i)
{
	char	*new;
	char	c;

	new = NULL;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				if (str[i] == '\\' && str[i + 1] && c == '"'
					&& (str[i + 1] == '"' || str[i + 1] == '$'))
					i++;
				new = ft_str_chr_cat(new, str[i++]);
			}
			i += str[i] == c ? 1 : 0;
		}
		else if (str[i] == '\\')
			i++;
		else
			new = ft_str_chr_cat(new, str[i++]);
	}
	return (new);
}

int				prompt_heredoc(char *eof, t_token *redir, t_control **history)
{
	t_cmd		cmd_hd;
	int			*io;
	int			i;

	i = 0;
	io = singleton_ioheredoc();
	cmd_hd = init_cmd("heredoc> ");
	save_cmd(&cmd_hd);
	isatty(0) ? ft_putstr("heredoc> ") : 0;
	eof = eof_quote(eof, i);
	cmd_hd.eof = ft_strdup(eof);
	ft_strdel(&eof);
	while (!cmd_hd.end_eof && !cmd_hd.stop)
		key_handler(&cmd_hd, history, NULL);
	*io = ft_isdigit((redir->token)[0]) ? ft_atoi(redir->token) : 0;
	ft_strdel(&(redir->token));
	redir->token = ft_strapp(redir->token, "<< ");
	redir->token = ft_strapp(redir->token, cmd_hd.str_quote);
	clear_cmd(&cmd_hd);
	save_cmd(NULL);
	return ((!cmd_hd.stop) ? 1 : 0);
}
