/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:52:37 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 15:18:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			error_export(char *name)
{
	ft_putstr_fd("shell: export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("':not a valid identifier\n", 2);
	return (0);
}
