/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:19:13 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/26 11:19:16 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			print_alloc_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int			error_env(size_t *i)
{
	free(i);
	return (1);
}

void		end_ft_env(size_t *i, char **env)
{
	if (i[2])
		env_tab(env);
	free(i);
}
