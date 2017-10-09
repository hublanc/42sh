/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 13:59:40 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/09 16:39:50 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			cd(char **path, char ***env);
int			change_envpwd(char *tmp, char ***env);
char		*get_elem(char ***env, char *elem);
char		*check_path(char *path, char ***env, char opt);
void		check_dotdot(char **tmp, char **path);
