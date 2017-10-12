/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 17:27:30 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 15:10:56 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "line_editor.h"

typedef struct		s_token
{
	char			*token;
	enum
	{
		NONE,
		WORD,
		QUOTE,
		REDIRECTION,
		PIPE,
		SEMI_COLON,
		IO_NUMBER,
		ET,
		OU,
	}				e_type;
	struct s_token	*next;
}					t_token;

typedef struct		s_node
{
	int				value;
	char			*token;
	int				wait;
	int				pipe;
	int				end_pipe;
	int				in;
	int				out;
	int				in_pipe;
	int				do_it;
	int				redir_r;
	int				redir_l;
	int				heredoc;
	int				aggre;
	int				*aggre_in_nb;
	char			**aggre_in_w;
	int				*aggre_out_nb;
	char			**aggre_out_w;
	char			*heredoc_str;
	int				*fd_out;
	int				*fd_out_io;
	int				*fd_in;
	int				*fd_in_io;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct		s_pidp
{
	pid_t			pid;
	struct s_pidp	*next;
}					t_pidp;

/*
**	Routine.c
*/
void				routine(char *cmd, char ***env, t_control **history);

/*
**	Exec.c
*/
int					check_cmd(char **tab, char **env, t_node *tree);
void				get_cmd(t_node *tree, char ***env, int *status,
					t_control **hist);

/*
**	Check_binary
*/
int					check_binary(char **args, char **env, char **cmd);

/*
**	Ft_cmdsplit.c
*/
char				**ft_cmdsplit(char *str);

/*
**	Extra_exec.c
*/
void				add_quote_content(char *str, char *new, int *i, int *j);
int					*singleton_status(void);

/*
**	Builtin.c
*/
int					built_in(t_node *tree, char **tab, char ***env,
					t_control **his);
int					builtin_tab(char **tab);

/*
**	Manage_pid.c
*/
t_pidp				**singleton_pid();
void				fetch_pid(pid_t pid);
void				wait_allpid();

/*
**	Pid_pipe.c
*/
t_pidp				*new_pid(pid_t pid);
void				add_pid(t_pidp **list, t_pidp *new);
void				delone_pid(t_pidp **list);
void				del_pid(t_pidp **list);

#endif
