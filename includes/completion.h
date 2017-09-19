/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:50:30 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 12:41:01 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

#include <dirent.h>

typedef struct		s_compl
{
	char			*arg;
//	int				type; //couleur
	struct s_compl	*next;
}					t_compl;

/*
** completion.c
*/
int					completion(t_cmd *cmd,char ***env);

/*
** list_args.c
*/
void				list_compl(t_compl *compl, char *arg, char ***env);

/*
** list_args.c
*/
void				get_args(t_compl *compl, char **paths, char *arg);

#endif
