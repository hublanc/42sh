# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mameyer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/06 20:38:30 by mameyer           #+#    #+#              #
#    Updated: 2017/09/07 13:13:05 by mameyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libdll.a

SRC =		dll_isempty.c \
			dll_add_new_elem_front.c \
			dll_add_new_elem_end.c \
			dll_del_elem_end.c \
			dll_del_elem_front.c \
			dll_print_list.c \
			dll_clear_list.c

OBJ =	$(patsubst %.c,%.o,$(SRC))

HEADER = ft.h

all : $(NAME)

$(NAME) :
	@ gcc -c $(SRC) -I $(HEADER) -Wall -Wextra -Werror
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)
	@ echo "COMPILATION SUCCESS"

clean :
	@ rm -f $(OBJ)
	@ echo "ALL .o FILES HAVE BEEN DELETED"
	@ echo "CLEANING SUCCESS"

fclean : clean
	@ rm -f $(NAME)

re : fclean all

.PHONY : all re clean fclean
