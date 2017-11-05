/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 17:52:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/28 18:31:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	err_nofordir(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
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

int		env_tab(char **env)
{
	disp_tab(env);
	return (0);
}

int		return_status(void)
{
	int		*status;

	status = singleton_status();
	return (*status);
}
