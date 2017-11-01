/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_isatty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:06:24 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/01 16:04:32 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	history_isatty(char *search)
{
	tputs(tgetstr("cd", NULL), 1, tputchar);
	ft_putstr("(reverse-i-search)`");
	ft_putstr(search);
	ft_putstr("': ");
}
