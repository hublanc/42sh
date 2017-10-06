/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 18:15:34 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:39:43 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

/*
**	Filedescriptor.c
*/
int			open_file(t_node *tree);
void		close_fd(t_node *tree);
void		manage_fd(t_node *tree);
void		prep_fd(t_node *tree);

/*
**	Aggre.c
*/
void		manage_aggre(t_node *cmd, t_node *redir);
void		exec_aggre(t_node *tree);

/*
**	Heredoc.c
*/
void		prompt_heredoc(char *eof, t_token *redir, t_control **history);
void		heredoc_input(t_node *tree);

/*
**	Pipe.c
*/
t_token		*prompt_pipe(t_token *list);

#endif
