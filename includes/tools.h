/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 18:24:56 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 14:29:01 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

/*
**	Error.c
*/
int			print_error(int err, char *cmd);
void		print_usage(char c);
int			check_access(char *path);
int			pwdnotset(char ***env);

/*
** signals.c
*/
void		reset_cmdsiginted(t_cmd *cmd);
int			is_sigint(int sigint);
int			can_sigint(int sigint);
void		get_signal(int n);
void		signal_do_nothing(int n);
void		event_not_found(char *str);

/*
**	Tools.c
*/
void		del_tabstr(char ***str);
void		disp_tab(char **str);
int			len_array(char **str);
int			stop_shell(char ***env, char **tab, t_control **history);
char		**get_env(char **env, int add);

/*
**	Tools_extra.c
*/
void		err_nofordir(char *cmd);
void		ft_putcolor(char *prompt);
t_token		*abort_sort(t_token *list, char *error);
int			env_tab(char **env);
int			return_status(void);

/*
**	Tools_history.c
*/
void		add_hist_or_not(t_control **history, char *str);
void		change_cmd(char *new, t_cmd *cmd);
t_lst		*seek_next_select(t_control **list);
void		seek_next(t_control **list, t_cmd *cmd);
t_lst		*seek_prev_select(t_control **list);
void		seek_prev(t_control **list, t_cmd *cmd);
void		set_selected_null(t_control **history);
void		delete_elem(t_lst **tmp);
int			check_space(char *str);

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
**	Tools_routine.c
*/
void		operator_or(t_node *tree);
void		operator_and(t_node *tree);
void		wait_flag(t_node *tree);
void		end_flag(t_node *tree);
void		pipe_flag(t_node *tree);

/*
**	tools_compl.c
*/
int			nbr_perline(int maxlen, int w);
int			nbr_percol(int nbrargs, int nbrperline);
int			maxrow_line(int lenline, int w);
char		*get_envpath(char ***env);
int			check_lname(char *n1, char *n2, int len);

/*
**	tools_cd.c
*/
void		ssupprchr(char **s, int pos);
void		saddchr(char **s, char c, int pos);
char		*get_elem(char ***env, char *elem);
void		check_isenvpwd(char ***env);

/*
** tools_env.c
*/
int			print_alloc_error(char *str);
int			error_env(size_t *i);
void		end_ft_env(size_t *i, char **env);

/*
**	tools_wd_designators.c
*/

int			error_bad_wspec(int digit, char ***splitted);
void		atoi_free(int *digit, char **test);
int			tablen(char **tab);

/*
**	tools_tty.c
*/
int			ttyyyy(int i);
int			check_in(struct termios term, int i);

#endif
