/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:50:54 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/20 14:31:43 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>

# include <termcap.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>

# include "exec.h"
# include "lexer.h"
# include "redirection.h"
# include "line_editor.h"
# include "tools.h"
# include "completion.h"

# define CYN	"\x1B[36m"
# define RESET	"\x1B[0m"

/*
**	g_is_child help to know if a child processus is in or not
*/

int					g_is_child;
struct termios		g_term;

/*
**	Built-in
*/
void		ft_echo(char **tab);
int			in_env(char *str, char **env);
void		ft_setenv(char **tab, char ***env);
void		ft_unsetenv(char **tab, char ***env);
void		ft_env(char **env, char **tab);
void		ft_cd(char **tab, char ***env);

char		**delonenv(char *name, char **env);
char		**prep_setenv(char *name, char *value);

/*
**	terminal
*/
void		set_terminal(void);
void		reset_term(void);
void		reset_disp(void);
int			tputchar(int c);

#endif
