/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:52:53 by hublanc           #+#    #+#             */
/*   Updated: 2017/09/13 19:45:01 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	err_nofordir(char *cmd, char ***tab)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	del_tabstr(tab);
	exit(EXIT_FAILURE);
}

void	ft_putcolor(char *prompt)
{
	ft_putstr(CYN);
	ft_putstr(prompt);
	ft_putstr(RESET);
}

t_token	*abort_sort(t_token *list, char *error)
{
	ft_putstr_fd("parse error near ", 2);
	ft_putendl_fd(error, 2);
	del_token(&list);
	return (list);
}
