/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:36:09 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/14 14:13:51 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITOR
# define LINE_EDITOR

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
	int				end_eof;
	int				line;
	int				col;
	int				sc_col;
	int				sc_row;
}					t_cmd;

typedef struct		s_hist
{
	char			*cmd;
	int				selected;
	int				current;
	struct s_hist	*next;
}					t_hist;

/*
**	Keys.c
*/
void		key_handler(t_cmd *cmd, t_control **history, char ***env);
void		print_line(t_cmd *cmd);
void		choose_prompt(t_cmd *cmd);

/*
**	Arrow.c
*/
void		arrow_handler(char *str, t_cmd *cmd, t_control **hist);

/*
**	Cmd.c
*/
t_cmd		init_cmd(char *prompt);
void		clear_cmd(t_cmd *cmd);
void		init_screen(t_cmd *cmd);

/*
**	History.c
*/
t_hist		*new_history(char *cmd);
void		add_begin(t_hist **list, t_hist *new);
void		delone_history(t_hist **list);
void		del_history(t_hist **list);
void		del_current(t_hist **list);

/*
**	Quote.c
*/
char		check_quote(char *str);
void		prompt_quote(t_cmd *cmd, t_control **history, char c, int mod);
void		prompt_backslash(t_cmd *cmd, t_control **history, int mod);

/*
**	Prompt.c
*/
int			print_prompt(void);
char		*return_prompt(void);

/*
**	Cut_copy_paste.c
*/
void		copy_cut_paste_handler(t_cmd *cmd, char *macro);

/*
**	Load_history.c
*/
t_control	*load_history();
void		save_history(t_control **history, char *str);
int			get_history_file_size(char *file_name);
void		save_history_in_file(t_control **history, char *file_name);

/*
**	Enter_handler.c
*/
void		enter_hub(t_cmd *cmd, t_control **history, char ***env);

/*
**	History search
*/

void		history_search(t_control **history, t_cmd *cmd, char ***env);

/*
**	last_command.c
*/

char		*last_command(char *command, t_control **history);

int			is_spec(char c);
int			is_d_dot(char *str);
void		set_error(int a, char *command);
void		modify_quotes(int *sq, int *dq, char c);
char		*wd_designator(char *command, t_control **history);
void		wd_designator_2(char *command, int *index, char **str, t_control **history);
void		get_d_bang(char *command, char **str, t_control **history, int *index);
void		get_last_command(char *command, char **str, t_control **history, int *index);
void		get_old_flags(char *command, char **str, t_control **history, int *index);
void		get_line_again(char *command, int *index, char **str, t_control **history);
void		get_last_sub(char *command, int *index, char **str, t_control **history);
int			check_sub_synt(char *command);
char		**split_spec(char *command);
void		get_n_first(char *command, char **str, t_control **history, int *index);
void		get_n_last(char *command, char **str, t_control **history, int *index);



#endif
