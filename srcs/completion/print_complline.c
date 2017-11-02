/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_complline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:56:43 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/02 12:35:42 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_linearg(t_compl *compl, char **buff, int *size, int *len)
{
	char	*tmp;

	if (compl->ar && compl->ar->arg && (tmp = ft_strdup(compl->ar->arg)))
	{
		buffcat(buff, tmp);
		*len += ft_strlen(tmp);
		if (*len % size[0] == 0)
			buffcat(buff, tgetstr("cr", NULL));
		if (*len % size[0] == 0)
			buffcat(buff, tgetstr("do", NULL));
		free(tmp);
	}
}

void		print_complline(t_compl *compl, t_cmd *cmd, int *size, char **buff)
{
	char	*tmp;
	int		len;

	buffcat(buff, tgetstr("cr", NULL));
	print_buff(buff);
	choose_prompt(cmd);
	len = 0;
	if ((tmp = ft_strndup(cmd->str, cmd->col - 1 - cmd->prlen
					- ((compl->curr >= 0) ? ft_strlen(compl->arg) : 0))))
	{
		buffcat(buff, tmp);
		len = cmd->prlen + ft_strlen(tmp) - 1;
		len += len % size[0] == 0 ? 0 : 1;
		if (len % size[0] == 0)
			buffcat(buff, tgetstr("cr", NULL));
		if (len % size[0] == 0)
			buffcat(buff, tgetstr("do", NULL));
		len = cmd->prlen + ft_strlen(tmp);
		free(tmp);
	}
	print_linearg(compl, buff, size, &len);
	buffcat(buff, tgetstr("sc", NULL));
	buffcat(buff, cmd->str + cmd->col - 1 - cmd->prlen);
	buffcat(buff, tgetstr("rc", NULL));
}

static void	reprint_line(t_compl *compl, t_cmd *cmd)
{
	struct winsize	w;
	char			*tmp;
	int				len;

	ioctl(0, TIOCGWINSZ, &w);
	go_begin(cmd->col + ((compl->ar) ? ft_strlen(compl->ar->arg) : 0),
			w.ws_col);
	choose_prompt(cmd);
	if ((tmp = ft_strndup(cmd->str, cmd->col - 1 - cmd->prlen)))
	{
		ft_putstr(tmp);
		len = cmd->prlen + ft_strlen(tmp);
		len = len % w.ws_col == 0 ? 0 : 1;
		if (len % w.ws_col == 0)
			ft_putstr(tgetstr("cr", NULL));
		if (len % w.ws_col == 0)
			ft_putstr(tgetstr("do", NULL));
		free(tmp);
	}
}

void		add_argtoline(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*args;
	int			i;

	if (compl->curr < 0)
		return ;
	args = &compl->args;
	while (args && compl->curr != args->id)
		args = args->next;
	i = ft_strlen(compl->arg);
	while (i-- && cmd->col > cmd->prlen + 1)
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		go_left(cmd);
	}
	reprint_line(compl, cmd);
	if (args && args->arg)
		add_line(cmd, args->arg);
	if (args && args->color && ft_strcmp("\e[1;36m", args->color))
		add_line(cmd, " ");
}

void		compl_addline(t_cmd *cmd, t_compl *compl)
{
	int	i;

	i = ft_strlen(compl->arg);
	while (i-- && cmd->col > cmd->prlen + 1)
	{
		cmd->str = ft_strdelone(cmd->str, (cmd->col - 1) - cmd->prlen);
		go_left(cmd);
	}
	add_line(cmd, compl->args.arg);
}
