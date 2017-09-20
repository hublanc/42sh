/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libdll.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:05:18 by mameyer           #+#    #+#             */
/*   Updated: 2017/09/19 17:44:50 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBDLL_H

# define LIBDLL_H

# include "libft.h"

typedef struct			s_control
{
	int					length;
	struct s_lst		*begin;
	struct s_lst		*end;
}						t_control;

typedef struct			s_lst
{
	char				*name;
	int					selected;
	int					current;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

t_control				*dll_new_list(void);
int						dll_is_empty(t_control *control);

t_control				*dll_add_new_elem_frnt(t_control *control, char *value);
t_control				*dll_add_new_elem_end(t_control *control, char *value);

t_control				*dll_del_elem_front(t_control *control);
t_control				*dll_del_elem_end(t_control *control);

t_control				*dll_clear_list(t_control *control);

void					dll_print_list(t_control *control, char sep);

#endif
