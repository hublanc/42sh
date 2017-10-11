/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_statement.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:58:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/11 17:34:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_STATEMENT_H
# define PROMPT_STATEMENT_H

# include <time.h>

void	add_backslash(char **line, int *i);
void	add_escape(char **line, int *i);
char	*before_curr_after(char **before, char *curr, char **after);
void	del_backslash(char **line, int *i);
void	join_free_all(char **date, int do_itoa);
void	get_date_prompt(char **line, int *i);
void	get_hostname_prompt(char **line, int *i, int mode);
void	get_octal_value(char **line, int *i, char *code);
void	prompt_path(char **line, int *i, int mode);
void	get_shell_name(char **line, int *i);
void	get_time_prompt(char **line, int *i, int mode);
void	get_time_prompt2(char **line, int *i);
void	get_ttyname(char **line, int *i);
void	get_uid_prompt(char **line, int *i);
void	get_username(char **line, int *i);
void	get_version(char **line, int *i, int mode);
void	prompt_management(char **line);

#endif
