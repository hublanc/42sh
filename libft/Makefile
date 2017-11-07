# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hublanc <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 12:07:21 by hublanc           #+#    #+#              #
#    Updated: 2017/11/07 17:29:21 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_strlen.c ft_strdup.c ft_strcmp.c ft_strcpy.c ft_strncpy.c\
	  ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strncmp.c\
	  ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c\
	  ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c ft_putchar.c ft_putstr.c ft_putendl.c\
	  ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c ft_strsplit.c\
	  ft_strtrim.c ft_strjoin.c ft_strsub.c ft_strequ.c ft_strnequ.c ft_strmapi.c ft_strmap.c ft_striter.c\
	  ft_striteri.c	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c\
	  ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_realloc.c ft_str_chr_cat.c ft_strapp.c ft_strappdel.c\
	  ft_putcharbuf.c ft_swaptr.c get_next_line.c ft_strdelone.c ft_strappone.c ft_putnbrel.c\
	  ft_strndup.c ft_strfullnb.c dll_add_new_elem_end.c dll_add_new_elem_front.c dll_clear_list.c dll_del_elem_end.c\
	  dll_del_elem_front.c dll_isempty.c dll_print_list.c ft_strschr.c ft_strschr_len.c\
	  ft_power.c ft_strlen_chr.c ft_getopt.c ft_strapphead.c ft_strstr_len.c ft_strtrimlast.c

OBJ = $(SRC:.c=.o)	

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

LIBINC = ./includes/

NAME = libft.a

RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
RESET = "\x1B[0m"

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "\r\c"
	@tput cd
	@echo $(GREEN)"libft.a created"$(RESET)

%.o: %.c $(LIBINC)
	@$(CC) -o $@ -c $< $(FLAGS) -I $(LIBINC)
	@echo "\r\c"
	@tput cd
	@echo $(YELLOW)$@" done"$(RESET)"\c"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
