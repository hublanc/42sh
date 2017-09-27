/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_complline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:56:43 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/27 17:00:40 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	print_linearg(t_compl *compl, char **buff, int *size, int *len)
{
	char	*tmp;

	if (compl->ar && compl->ar->arg
			&& (tmp = ft_strdup(compl->ar->arg + ft_strlen(compl->arg))))
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

	print_buff(buff);
	choose_prompt(cmd);
	len = 0;
	if ((tmp = ft_strndup(cmd->str, cmd->col - 1 - cmd->prlen)))
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
