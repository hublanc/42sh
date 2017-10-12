/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 13:48:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/12 11:57:06 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct		s_loc
{
	char			*name;
	char			*value;
	struct s_loc	*next;
}					t_loc;

/*
**	cmd_loc.c
*/
int					gest_loc(char **cmmd, char ***env);

/*
**	local.c
*/
void				add_loc(char *name, char *val, char ***env);
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
