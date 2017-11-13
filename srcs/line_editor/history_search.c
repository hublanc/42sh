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

int			*singleton_len_prev(void)
{
	static int		s_lenprev = 0;

	return (&s_lenprev);
}

void		set_lenprev(int val)
{
	int		*len;

	len = singleton_len_prev();
	*len = val;
}

int			return_lenprev(void)
{
	int		*len;

	len = singleton_len_prev();
	return (*len);
}

char		*history_search(t_control **history)
{
	char		buf[4];
	char		*search;
	t_lst		*tmp;

	if (!(*history) || (*history && (*history)->length < 1))
		return (0);
	init_hist_search(&search, &tmp);
	ft_strclr(buf);
	while (read(0, &buf, 4))
	{
		if (is_sigint(0))
			return (return_sigint_2(&search, buf));
		if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126)
			break ;
		else if (ft_isprint(buf[0]) || (buf[0] == 127)
			|| (buf[0] == 27 && tmp))
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
		set_lenprev(0);
		ft_strdel(search);
		return (ft_strdup(tmp->name));
	}
	else if (!ft_isprint(buf[0]) && !ft_isprint(buf[1]) && !ft_isprint(buf[2])
			&& ft_strlen(*search) == 0 && buf[0] != 10)
		exit(0);
	else
	{
		ft_strclr(buf);
		set_lenprev(0);
		ft_strdel(search);
		ft_putchar('\n');
		return (NULL);
	}
}
