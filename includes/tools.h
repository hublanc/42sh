/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 18:24:56 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:39:52 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

typedef struct			s_control
{
	int					length;
	struct s_lst		*begin;
	struct s_lst		*end;
}						t_control;

typedef struct			s_lst
{
	char				*name;
	int					type;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

/*
**	Error.c
*/
void		print_error(int err, char *cmd);
void		print_usage(char c);
int			check_access(char *path, char **env);
int			pwdnotset(char ***env);
void		get_signal(int n);

/*
**	Tools.c
*/
void		del_tabstr(char ***str);
void		disp_tab(char **str);
int			len_array(char **str);
void		stop_shell(char ***env, char **tab, t_hist **history);
char		**get_env(char **env, int add);

/*
**	Tools_extra.c
*/
void		err_nofordir(char *cmd, char ***tab);
void		ft_putcolor(char *prompt);
t_token		*abort_sort(t_token *list, char *error);

/*
**	Tools_history.c
*/
void		change_cmd(char *new, t_cmd *cmd);
t_hist		*seek_next_select(t_hist *list);
void		seek_next(t_hist **list, t_cmd *cmd);
t_hist		*seek_prev_select(t_hist *list);
void		seek_prev(t_hist **list, t_cmd *cmd);

/*
**	Tools_keys.c
*/
void		go_begin(int pos, int col);
void		go_right(t_cmd *cmd);
void		go_left(t_cmd *cmd);
void		seek_lword(t_cmd *cmd);
void		seek_rword(t_cmd *cmd);

/*
**	Tools_lexer.c
*/
char		*jump_quote(char *cmd, char **new, int *i);
char		*jump_bs(char *cmd, char **new, int *i);
void		token_chevron(t_token **list, char *cmd);
int			check_chevron(t_token **list, char *cmd);
int			check_number(t_token **list, char *cmd);

/*
**	Tools_redir.c
*/
int			*add_fd(int *fds, t_node *tree);
int			*add_io(int *fds, t_node *tree, int io);
char		**add_w(char **tab, t_node *tree, int cut);

/*
**	Tools history
*/

int			dll_is_empty(t_control *control);
t_control	*dll_add_new_elem_frnt(t_control *control, char *value);
t_control	*dll_clear_list(t_control *control);

#endif
