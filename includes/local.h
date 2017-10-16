/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:48:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/16 19:38:20 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_H

# define LOCAL_H

typedef struct		s_loc
{
	char			*name;
	char			*value;
	struct s_loc	*next;
}					t_loc;

/*
**	cmd_loc.c
*/
int					gest_loc(char **cmmd);

/*
**	local.c
*/
void				add_loc(char *name, char *val);
void				suppr_loc(char *name);
t_loc				*get_loc(char *name);

/*
**	unset.c
*/
int					unset(char **tab, char ***env);

/*
**	export.c
*/
int					export(char **tab, char ***env);

#endif
