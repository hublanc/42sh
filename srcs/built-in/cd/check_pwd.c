/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 10:09:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/16 10:10:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_pwd(char **pwd, char *to_append)
{
	if (pwd && !*pwd)
	{
		*pwd = ft_strnew(PATH_MAX + 1);
		getcwd(*pwd, PATH_MAX);
	}
	else if (pwd)
	{
		*pwd = ft_strdup(*pwd);
		if (*pwd && (*pwd)[0])
			add_slash(pwd);
		*pwd = ft_strapp(*pwd, to_append);
	}
}
