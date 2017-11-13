/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 17:27:30 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:41:27 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "line_editor.h"

typedef struct		s_hash
{
	char			*value;
	char			*path;
	int				key;
	struct s_hash	*next;
}					t_hash;

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
	int				hd;
	int				hd_io;
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
char				**get_bin(char **env, int pos);
int					reset_status(void);

/*
**	Ft_cmdsplit.c
*/
char				**ft_cmdsplit(char *str);

/*
**	Extra_exec.c
*/
void				add_quote_content(char *str, char *new, int *i, int *j);
int					*singleton_status(void);
void				reset_var(int *input, int *fd1, int *fd2);
int					*singleton_fail(void);
int					get_fail(void);

/*
**	Builtin.c
*/
int					built_in(t_node *tree, char **tab, char ***env,
					t_control **his);
int					builtin_tab(char *str);

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

/*
**	Hash.c
*/
t_hash				*new_hash(char *value, char *path, int key);
t_hash				*add_hash(t_hash *list, t_hash *new);
void				delone_hash(t_hash **list);
void				del_hash(t_hash **list);

/*
**	Extra_hash.c
*/
int					is_in_htable(char *value, char **cmd);
t_hash				*seek_value(char *value);
void				add_hash_table(char *path, char *value);
int					get_key(char *value);
t_hash				**singleton_hash(void);

/*
**	Is_modif.c
*/
char				**singleton_path(char *path);
void				load_path(char **env);
void				is_modif(char **env);
void				del_spath(void);

#endif
