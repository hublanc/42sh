/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:50:54 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:38:58 by hublanc          ###   ########.fr       */
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
# include "line_editor.h"
# include "redirection.h"
# include "tools.h"

# define CYN	"\x1B[36m"
# define RESET	"\x1B[0m"

typedef struct		s_hist_flags
{
	int				c;
	int				d;
	int				a;
	int				n;
	int				r;
	int				w;
	int				p;
	int				s;
}					t_hist_flags;

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
void		ft_history(char **tab, char ***env, t_control **history);

char		**delonenv(char *name, char **env);
char		**prep_setenv(char *name, char *value);

/*
**	terminal
*/
void		set_terminal(void);
void		reset_term(void);
void		reset_disp(void);
int			tputchar(int c);

/*
**	History_builtin
*/

void		init_cd_flags(t_hist_flags *flags);
void		get_cd_flags(t_hist_flags *flags, char **tab);
void		set_usage(char c, int type);
void		print_history(t_control **history);
int			get_num(int size);
void		delete_elem_hist(int index, t_control **history);
int			str_isdigit(char *str);
void		print_pflag(char **tab);

#endif
