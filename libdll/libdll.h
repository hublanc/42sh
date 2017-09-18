/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libdll.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 06:05:18 by mameyer           #+#    #+#             */
/*   Updated: 2017/08/30 07:16:24 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBDLL_H

# define LIBDLL_H

# include "../libft/libft.h"

# define UNSET 0
# define COMMAND 1
# define AND 2
# define PIPE 3
# define REDIRECTION 4

typedef struct			s_control
{
	int					length;
	struct s_lst		*begin;
	struct s_lst		*end;
}						t_control;

typedef struct			s_lst
{
	char				*name;
	int					type;
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
