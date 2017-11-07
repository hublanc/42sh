/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_copy_paste3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 20:42:22 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/07 16:27:13 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		print_charev(t_cmd *cmd)
{
	if (!ttyyyy(0))
		return ;
	tputs(tgetstr("mr", NULL), 1, tputchar);
	ft_putchar((cmd->str)[(cmd->col - 1) - cmd->prlen]);
	tputs(tgetstr("me", NULL), 1, tputchar);
}

void		print_up(int nb, int n)
{
	if (!ttyyyy(0))
		return ;
	tputs(tgetstr("sc", NULL), 1, tputchar);
	tputs(tgetstr("ho", NULL), 1, tputchar);
	ft_putnbr(nb);
	tputs(tgetstr("do", NULL), 1, tputchar);
	ft_putnbr(n);
	tputs(tgetstr("rc", NULL), 1, tputchar);
}
