/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editor.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 16:36:09 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/18 13:56:45 by amazurie         ###   ########.fr       */
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
	int				stop;
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
void		key_handler(t_cmd *cmd, t_hist **history, char ***env);
void		print_line(t_cmd *cmd);
void		choose_prompt(t_cmd *cmd);

/*
**	Arrow.c
*/
void		arrow_handler(char *str, t_cmd *cmd, t_hist **hist);

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
void		prompt_quote(t_cmd *cmd, t_hist **history, char c, int mod);
void		prompt_backslash(t_cmd *cmd, t_hist **history, int mod);

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
t_hist		*load_history();
void		save_history(t_hist **history, char *str);

/*
**	Enter_handler.c
*/
void		enter_hub(t_cmd *cmd, t_hist **history, char ***env);

#endif
