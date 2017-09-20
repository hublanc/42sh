/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 09:50:30 by amazurie          #+#    #+#             */
/*   Updated: 2017/09/20 13:56:28 by amazurie         ###   ########.fr       */
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
//	int				lencurr;
	int				nbrargs;
	char			*arg;
	struct s_coargs	args;
}					t_compl;

/*
** completion.c
*/
int					completion(t_cmd *cmd, char ***env, char **buf);

/*
** list_args.c
*/
void				list_compl(t_compl *compl, char ***env);

/*
** get_binaries.c
*/
void				get_args(t_compl *compl, char **paths);

/*
** print_args.c
*/
void		display_args(t_compl *compl, t_cmd *cmd);

/*
** compl_keys.c
*/
int			compl_keys(t_compl *compl, t_cmd *com, char **buf);

#endif
