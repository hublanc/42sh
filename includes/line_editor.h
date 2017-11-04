/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:36:09 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 13:35:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITOR_H
# define LINE_EDITOR_H

typedef struct		s_cmd
{
	char			*str;
	char			*str_quote;
	char			*eof;
	char			*prompt;
	char			*buffer;
	char			*save_cmd;
	int				prlen;
	int				end_bs;
	int				end_pp;
	int				end_eof;
	int				line;
	int				col;
	int				sc_col;
	int				sc_row;
	int				stop;
}					t_cmd;

typedef struct		s_bang
{
	char			*result;
	char			*to_append;
	char			*command;
	int				index;
	int				len;
	int				quotes;
}					t_bang;

typedef struct		s_bang2
{
	int				begin;
	int				end;
	char			*cmd;
	int				d_bang;
	int				q_mark;
	int				hash_t;
	int				cmd_l;
	int				n_set;
	char			c_x;
	char			c_y;
	int				dash;
	int				x;
	int				y;
	int				m_h;
	int				m_t;
	int				m_r;
	int				m_e;
	int				m_p;
	int				m_q;
	int				m_x;
	int				m_s;
	int				m_g;
	char			*old;
	char			*new;
	char			*str;
}					t_bang2;

/*
**	Event_designators.c
*/

char				*bang_events(char *command, t_control **history);
int					bang_events_2(t_bang **bang, t_control **history);
int					bang_events_3(t_bang **bang, t_control **history);

int					get_elem_hist(t_bang **bang, t_control **history);
int					get_elem_hist_2(t_bang **bang, t_control **history, int a);

int					get_double_bang(t_bang **bang, t_control **history, int a);
int					get_n_first(t_bang **bang, t_control **history, int a);
int					get_n_last(t_bang **bang, t_control **history, int a);
int					get_c_last(t_bang **bang, t_control **history, int a);

int					get_elem_arg(t_bang **bang, int a);
int					get_elem_arg_2(t_bang **bang, int a, int *digit);
int					word_designator(t_bang **bang, int a);
void				dollar_designator(t_bang **bang, char **split, int digit);
void				star_designator(t_bang **bang, char **splitted);

/*
**	Keys.c
*/
void				key_handler(t_cmd *cmd, t_control **history, char ***env);
void				key_handler_sigint(t_cmd *cmd,
					t_control **history, char ***env, char **buf);
char				*save_buf(char *buf);
int					return_void(t_cmd *cmd, t_control **history, char ***env);

/*
**	line_edit.c
*/
void				print_line(t_cmd *cmd);
void				choose_prompt(t_cmd *cmd);
void				add_line(t_cmd *cmd, char *buf);

/*
**	Arrow.c
*/
void				control_homend(char *str, t_cmd *cmd);
void				arrow_handler(char *str, t_cmd *cmd, t_control **hist);

/*
**	Cmd.c
*/
t_cmd				init_cmd(char *prompt);
void				clear_cmd(t_cmd *cmd);
void				init_screen(t_cmd *cmd);
t_cmd				*save_cmd(t_cmd *cmd);

/*
**	Quote.c
*/
char				check_quote(char *str);
void				prompt_quote(t_cmd *cmd, t_control **history, char c,
					int mod);
void				prompt_backslash(t_cmd *cmd, t_control **history, int mod);

/*
**	Cmdandor.c
*/
int					check_cmdandor(char *str);
void				prompt_cmdandor(t_cmd *cmd, t_control **history, int mod);
void				enter_handler_cmdandor(t_cmd *cmd, t_control **history);

/*
**	Prompt.c
*/
void				print_prompt(void);
char				*return_prompt(void);
size_t				strlen_prompt(char *prompt);

/*
**	Cut_copy_paste.c
*/
void				copy_cut_paste_handler(t_cmd *cmd, char *macro);

/*
**	Cut_copy_paste2.c
*/
void				right_handler(t_cmd *cmd, int *swap, int start);
void				left_handler(t_cmd *cmd, int *swap, int start);
void				cut_str(t_cmd *cmd, int start);
void				stock_buffer(t_cmd *cmd, int start);

/*
**	Cut_copy_paste3.c
*/
void				print_charev(t_cmd *cmd);
void				print_up(int nb, int n);

/*
**	Load_history.c
*/
t_control			*load_history(char **env);
void				load_history_2(int fd, t_control **history);
int					save_history(t_control **history, char *str, char *file);
int					get_history_file_size(char *file_name);
int					save_history_in_file(t_control **history, char *file_name);

/*
**	Enter_handler.c
*/
void				enter_hub(t_cmd *cmd, t_control **history, char ***env);

/*
**	History search
*/

int					history_search(t_control **history, char **str);
void				history_isatty(char *search);
t_lst				*history_search_2(t_control **history, char *search);
t_lst				*while_handler(char *buf, char **search,
					t_control **history, t_lst *tmp);
t_lst				*move_in_hist(t_lst *pos, char *buf, t_control **history);
void				set_search_prompt(char *search, t_lst *tmp, int type);
t_lst				*while_handler(char *buf, char **search,
					t_control **history, t_lst *tmp);
int					return_handler(t_lst *tmp, char *buf, char **search,
					char **str);
void				init_hist_search(char **search, t_lst **tmp);
int					return_sigint(char **to_del, char *to_save);

/*
**	Bang_1.c
*/
char				*deal_bang(char *cmd, t_control *hist);

/*
**	Word_designator.c
*/
int					word_designator_x(char *cmd, t_bang2 *bang, int i);
int					get_xdigit(char *cmd, t_bang2 *bang, int i);
int					word_designator_y(char *cmd, t_bang2 *bang, int i);
int					get_ydigit(char *cmd, t_bang2 *bang, int i);

/*
**	Event_designator.c
*/
int					event_designator(char *cmd, t_bang2 *bang, int i);

/*
**	Word_modifier.c
*/
int					word_modifier(char *cmd, t_bang2 *bang, int i);

/*
**	Get_line_hist.c
*/
char				**get_line_history(t_control *hist, t_bang2 *bang
					, char *final);

/*
**	Get_line_hist2.c
*/
char				**get_nline(t_control *hist, t_bang2 *bang);

/*
**	Get_splitted.c
*/
char				**designator_fnc(char **hist_line, t_bang2 *bang);
char				**return_error_bad_wspec(t_bang2 *bang, char **hist_line);
char				**dup_free_return(char **hist_line, int begin, int end);
void				find_begin(t_bang2 *bang, int *begin, int *end, char **hist_line);
void				find_end(t_bang2 *bang, int *begin, int *end, char **hist_line);

/*
**	bang_split.c
*/
char				**bang_split(char *str);

#endif
