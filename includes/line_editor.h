/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:36:09 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/31 14:42:25 by mameyer          ###   ########.fr       */
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
/*
typedef struct		s_hist
{
	char			*cmd;
	int				selected;
	int				current;
	struct s_hist	*next;
}					t_hist;
*/
/*
**	Keys.c
*/
void				key_handler(t_cmd *cmd, t_control **history, char ***env);
char				*save_buf(char *buf);

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

/*
**	word_designators.c
*/

char				*wd_designator(char *command, t_control **history);
int					wd_designator_2(char *command, int *a, char **result,
					t_control **history);
int					wd_designator_3(char *command, int *a, char **result,
					t_control **history);
int					wd_designator_4(char *command, int *a, char **result,
					t_control **history);
int					wd_designator_5(char *command, int *a, char **result,
					t_control **history);
int					wd_designator_6(char *command);
int					get_d_bang(char *command, int *a, char **result,
					t_control **history);
int					get_n_first(char *command, int *a, char **result,
					t_control **history);
int					get_n_first_2(char *command, int *a, char **str,
					char **result);
int					get_n_last(char *command, int *a, char **result,
					t_control **history);
int					get_n_last_2(char *command, int *a, char **str,
					char **result);
int					get_n_last_3(int nb, int *a, char **str);
int					get_c_first(char *command, int *a, char **result,
					t_control **history);
int					get_tmp_cfirst(t_lst **tmp, char *test, char **str);
int					get_c_first_2(char *command, int *a, char **str,
					char **result);
void				get_c_first_3(char **test, char *command, int *a, int b);
int					get_c_first_check_history(t_control **history, char **str,
					char **test);

void				modify_quotes(int *sq, char c, int *a);
void				d_dots_found(char *command, char **str, int b);
void				append_str(char *to_cpy, char **str);
int					get_tmp_lst(t_lst **tmp, int b, int nb, char **str);

/*
**	last_command.c			TO DELETE

char				*last_command(char *command, t_control **history);

void				set_error(int a, char *command);
void				modify_quotes(int *sq, int *dq, char c);
char				*wd_designator(char *command, t_control **history);
int					wd_designator_2(char *command, int *index, char **str,
					t_control **history);
int					get_d_bang(char *command, char **str, t_control **history,
					int *index);
int					get_last_command(char *command, char **str,
					t_control **history, int *index);
int					get_last_command_2(char *tmp, t_control **history,
					char **str);
void				get_last_command_3(char *str, int *index, char **tmp);
void				get_line_again(char *command, int *index, char **str,
					t_control **history);
int					get_n_first(char *command, char **str, t_control **history,
					int *index);
int					get_n_last(char *command, char **str, t_control **history,
					int *index);
*/

#endif
