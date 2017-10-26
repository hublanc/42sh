/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:42:22 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/26 14:50:06 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		print_charev(t_cmd *cmd)
{
	isatty(0) ? tputs(tgetstr("mr", NULL), 1, tputchar) : 0;
	ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]);
	isatty(0) ? tputs(tgetstr("me", NULL), 1, tputchar) : 0;
}

void		print_up(int nb, int n)
{
	isatty(0) ? tputs(tgetstr("sc", NULL), 1, tputchar) : 0;
	isatty(0) ? tputs(tgetstr("ho", NULL), 1, tputchar) : 0;
	ft_putnbr(nb);
	isatty(0) ? tputs(tgetstr("do", NULL), 1, tputchar) : 0;
	ft_putnbr(n);
	isatty(0) ? tputs(tgetstr("rc", NULL), 1, tputchar) : 0;
}
