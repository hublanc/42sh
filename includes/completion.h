/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:50:30 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/19 16:37:42 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

#include <dirent.h>

typedef struct		s_coargs
{
	int				id;
	char			*arg;
//	int				type; //couleur
	struct s_coargs	*next;
}					t_coargs;

typedef struct		s_compl
{
	size_t			maxlen;
	int				curr;
	int				nbrargs;
	char			*arg;
	struct s_coargs	args;
}					t_compl;

/*
** completion.c
*/
int					completion(t_cmd *cmd,char ***env);

/*
** list_args.c
*/
void				list_compl(t_compl *compl, char ***env);

/*
** list_args.c
*/
void				get_args(t_compl *compl, char **paths);

#endif
