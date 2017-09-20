/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:56:32 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/14 13:46:50 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	heredoc_input(t_node *tree)
{
	int		fd[2];

	pipe(fd);
	dup2(fd[0], 0);
	ft_putstr_fd(tree->heredoc_str, fd[1]);
	close(fd[1]);
}	

void	prompt_heredoc(char *eof, t_token *redir, t_control **history)
{
	t_cmd		cmd_hd;

	cmd_hd = init_cmd("heredoc> ");
	ft_putstr("heredoc> ");
	cmd_hd.eof = ft_strdup(eof);
	while (!cmd_hd.end_eof)
		key_handler(&cmd_hd, history, NULL);
	ft_strdel(&(redir->token));
	redir->token = ft_strapp(redir->token, "<< ");
	redir->token = ft_strapp(redir->token, cmd_hd.str_quote);
	clear_cmd(&cmd_hd);
}
