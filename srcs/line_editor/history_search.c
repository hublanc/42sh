/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:09:47 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 16:31:32 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*history_search(t_control **history)
{
	char		buf[3];
	char		*search;
	t_lst		*tmp;
	int			type;

	type = 0;
	if (!(*history) || (*history && (*history)->length < 1))
		return (0);
	init_hist_search(&search, &tmp);
	ft_strclr(buf);
	while (read(0, &buf, 3))
	{
		type++;
		if (is_sigint(0))
		{
			can_sigint(1);
			is_sigint(1);
			return (return_sigint(&search, buf));
		}
		if ((tmp || type == 1) && (ft_isprint(buf[0]) || (buf[0] == 127)
			|| (buf[0] == 27 && tmp)))
			tmp = while_handler(buf, &search, history, tmp);
		else if (buf[0] != 18)
			break ;
		ft_strclr(buf);
	}
	return (return_handler(tmp, buf, &search));
}

char		*return_handler(t_lst *tmp, char *buf, char **search)
{
	if (tmp && buf[0] == 10)
	{
		ft_strdel(search);
		return (ft_strdup(tmp->name));
	}
	else if (!ft_isprint(buf[0]) && !ft_isprint(buf[1]) && !ft_isprint(buf[2])
			&& ft_strlen(*search) == 0 && buf[0] != 10)
		exit(0);
	else
	{
		ft_putchar('\n');
		ft_strdel(search);
		return (NULL);
	}
}

t_lst		*while_handler(char *buf, char **search, t_control **history,
			t_lst *tmp)
{
	if (ft_isprint(buf[0]))
	{
		*search = ft_str_chr_cat(*search, buf[0]);
		tmp = history_search_2(history, *search);
		set_search_prompt(*search, tmp, 1);
	}
	else if (buf[0] == 127 && *search && ft_strlen(*search) <= 1)
	{
		if (ft_strlen(*search) == 1)
			*search = ft_strdelone(*search, ft_strlen(*search));
		set_search_prompt(*search, tmp, 0);
	}
	else if (buf[0] == 127 && *search && ft_strlen(*search) > 1)
	{
		*search = ft_strdelone(*search, ft_strlen(*search));
		tmp = history_search_2(history, *search);
		set_search_prompt(*search, tmp, 1);
	}
	else if (buf[0] == 27 && tmp)
	{
		tmp = move_in_hist(tmp, buf, history);
		set_search_prompt(*search, tmp, 1);
	}
	return (tmp);
}

static void	go_down(void)
{
	if (!ttyyyy(0))
		return ;
	tputs(tgetstr("cr", NULL), 1, tputchar);
	tputs(tgetstr("do", NULL), 1, tputchar);
}
/*
static void	pass_prompt(t_cmd *cmd)
{
	int		i;

	if (!isatty(2) || !ttyyyy(2))
		return ;
	i = 0;
	while (i < cmd->prlen)
	{
		if (i == cmd->sc_col)
			go_down();
		else
			tputs(tgetstr("nd", NULL), 1, tputchar);
		i++;
	}
}
*/
void		print_line2(t_cmd *cmd)
{
	int		len;

	if (!ttyyyy(0))
		return ;
	len = cmd->prlen + (int)ft_strlen(cmd->str);
	if (!len)
		return ;
	len += len % cmd->sc_col == 0 ? 0 : 1;
	go_begin(cmd->col, cmd->sc_col);
	ft_putstr(cmd->prompt);
//	pass_prompt(cmd);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr(cmd->str);
	if (len > cmd->col)
		while (len-- != cmd->col)
			tputs(tgetstr("le", NULL), 1, tputchar);
	else if (len < cmd->col)
		while (len != cmd->col && len > 0)
		{
			if (len % cmd->sc_col == 0)
				go_down();
			else
				tputs(tgetstr("nd", NULL), 1, tputchar);
			len++;
		}
}

void		set_search_prompt(char *search, t_lst *tmp, int type)
{
	struct winsize		z;
	char				*prompt;
	t_cmd				cmd;
	int					foundlen;

	(void)type;
	if (ioctl(0, TIOCGWINSZ, &z) == -1)
		return ;
	if (!tmp && ft_strlen(search) != 0)
		prompt = ft_strdup("failing reverse-i-search:` ");
	else
		prompt = ft_strdup("(reverse-i-search)`");	
	foundlen = 0;
	if (tmp)
		foundlen = ft_strlen(tmp->name);
	prompt = ft_strapp(prompt, search);
	prompt = ft_strapp(prompt, "': ");
	cmd = init_cmd(prompt);
	cmd.prlen = ft_strlen(prompt);
	cmd.sc_col = z.ws_col;
	cmd.col = ft_strlen(prompt) + foundlen;
	ft_strdel(&prompt);
	if (tmp)
		cmd.str = ft_strdup(tmp->name);
	else
		cmd.str = NULL;
	print_line2(&cmd);
}

/*
//	ft_putendl("TEST");
	print_line(&cmd);
//	ft_putendl("VICTORY");
	if (ioctl(0, TIOCGWINSZ, &z) == -1)
		return ;
	if (type == 0)
	{
		go_begin((ft_strlen(search) + 22), z.ws_col);
		ttyyyy(0) ? tputs(tgetstr("cd", NULL), 1, tputchar) : 0;
		ttyyyy(0) ? ft_putstr("(reverse-i-search)`': ") : 0;
		return ;
	}
	go_begin((ft_strlen(search) + 22), z.ws_col);
	if (ttyyyy(0))
		history_isatty(search);
	(tmp && ttyyyy(0)) ? ft_putstr(tmp->name) : 0;
	if (tmp)
		return ;
	go_begin((ft_strlen(search) + 26), z.ws_col);
	if (!ttyyyy(0))
		return ;
	if (ft_strlen(search) + 26 > z.ws_col)
	{
		tputs(tgetstr("up", NULL), 1, tputchar);
	}
//	ft_putendl("GO_BEGIN()");
//	go_begin((ft_strlen(search) + 26), z.ws_col);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr("failing reverse-i-search: ");
	ft_putstr(search);
	ft_putchar('_');
}*/

t_lst		*history_search_2(t_control **history, char *search)
{
	t_lst	*tmp;

	if (ft_strlen(search) < 1)
		return (NULL);
	tmp = NULL;
	if (history && (*history)->begin)
		tmp = (*history)->begin;
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->name, search) != 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
