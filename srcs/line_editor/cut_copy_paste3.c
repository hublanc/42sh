/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:42:22 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/26 16:51:33 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		print_charev(t_cmd *cmd)
{
	if (!isatty(0))
		return ;
	tputs(tgetstr("mr", NULL), 1, tputchar);
	ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]);
	tputs(tgetstr("me", NULL), 1, tputchar);
}

void		print_up(int nb, int n)
{
	if (!isatty(0))
		return ;
	tputs(tgetstr("sc", NULL), 1, tputchar);
	tputs(tgetstr("ho", NULL), 1, tputchar);
	ft_putnbr(nb);
	tputs(tgetstr("do", NULL), 1, tputchar);
	ft_putnbr(n);
	tputs(tgetstr("rc", NULL), 1, tputchar);
}
