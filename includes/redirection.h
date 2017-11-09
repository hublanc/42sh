/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 09:56:58 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/09 13:13:28 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

/*
**	Filedescriptor.c
*/
int			open_file(t_node *tree);
void		close_fd(t_node *tree);
int			manage_fd(t_node *tree);
int			prep_fd(t_node *tree);

/*
**	File.c
*/
int			open_file(t_node *tree);

/*
**	Aggre.c
*/
void		manage_aggre(t_node *cmd, t_node *redir);
int			exec_aggre(t_node *tree);

/*
**	Heredoc.c
*/
int			prompt_heredoc(char *eof, t_token *redir, t_control **history);
void		heredoc_input(t_node *tree);
void		manage_heredoc(t_node *tree, t_node *tmp);

/*
**	Pipe.c
*/
void		prompt_pipe(t_cmd *cmd, t_control **history, int mod);
void		enter_handler_pipe(t_cmd *cmd, t_control **history);
int			checkstr_pipe(char *cmd);

/*
**	Extra_redir.c
*/
int			do_redir(t_node *tree);
int			exec_dup(int fd1, int fd2);
int			len_io(char *str);
int			type_redir(char *str);
int			error_redir(char *file, char *reason);

#endif
