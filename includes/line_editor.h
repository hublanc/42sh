/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:36:09 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 16:21:33 by hublanc          ###   ########.fr       */
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
	int				pr_quote;
	int				pr_bs;
	int				pr_andor;
	int				pr_pipe;
	int				pr_here;
}					t_cmd;

typedef struct		s_bang2
{
	int				begin;
	int				end;
	char			*cmd;
	int				d_bang;
	int				q_mark;
	int				hash_t;
	int				cmd_l;
	int				shortcut;
	int				n_set;
	int				n_neg;
	char			c_x;
	char			c_y;
	int				dash;
	int				x;
	int				x_set;
	int				y;
	int				y_set;
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
**	Extra_enter.c
*/
void				t_istwo(int t, t_cmd *cmd);

/*
**	History search
*/

char				*history_search(t_control **history);
void				history_isatty(char *search);
t_lst				*history_search_2(t_control **history, char *search);
t_lst				*while_handler(char *buf, char **search,
					t_control **history, t_lst *tmp);
t_lst				*move_in_hist(t_lst *pos, char *buf, t_control **history);
void				set_search_prompt(char *search, t_lst *tmp, int type, int mode);
t_lst				*while_handler(char *buf, char **search,
					t_control **history, t_lst *tmp);
char				*return_handler(t_lst *tmp, char *buf, char **search);
void				init_hist_search(char **search, t_lst **tmp);
char				*return_sigint(char **to_del, char *to_save);
char				*return_sigint_2(char **to_del, char *to_save);
void				set_failing(char *search, struct winsize z, int mode);

int					*singleton_len_prev(void);
void				set_lenprev(int val);
int					return_lenprev(void);
void				go_up_ctrlr(struct winsize z);
void				go_down_ctrlr(void);

/*
**	Bang_1.c
*/
char				*deal_bang(char *cmd, t_control *hist, int *t);

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
void				find_begin(t_bang2 *bang, int *begin, int *end,
					char **hist_line);
void				find_end(t_bang2 *bang, int *begin, int *end,
					char **hist_line);

/*
**	bang_split.c
*/
char				**bang_split(char *str);

/*
**	modifiers.c
*/
void				rmpathname(char **arg);
void				rmpathcomp(char **arg);
void				rmsuffix(char **arg);
void				rmallbutsuffix(char **arg);
char				*quoteit(char *arg);

/*
**	Modifiers_quote.c
*/
char				*quoteword(char *arg);

/*
**	Modif_substi.c
*/
char				*modif_substi(char *arg, char *old, char *new, int rec);

/*
**	Extra_modif.c
*/
void				init_substi1(int *i, int *k, char *old, int j);
void				init_substi2(int *j, int *l, char *arg);
void				init_substi3(int *i, int *j, int *l, char *arg);
void				loop_substi(int *i, int *j, char *arg);
char				*free_str_return_null(char **str);

/*
**	do_modifiers.c
*/
char				**do_modifiers(char **tab, t_bang2 *bang);

/*
**	split_extra.c
*/
void				subspe(char *new, char *str, int *i, int *j);
void				init_var_bang(char *c, int *i, int *is_p);

#endif
