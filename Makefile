# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hublanc <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/24 15:04:09 by hublanc           #+#    #+#              #
#    Updated: 2017/10/24 13:02:33 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= shell
CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address
DFLAGS	= -MMD
LIB		= libft/libft.a
HEADER	= includes/
LIBSRC	= libft/
SRCDIR	= srcs/
OBJDIR	= objs/
SRC		=	main.c\
			terminal.c\
			line_editor/prompt.c\
			line_editor/arrow.c\
			line_editor/keys.c\
			line_editor/cmd.c\
			line_editor/quote.c\
			line_editor/history.c\
			line_editor/cmdandor.c\
			line_editor/line_edit.c\
			line_editor/load_history.c\
			line_editor/enter_handler.c\
			line_editor/cut_copy_paste.c\
			line_editor/cut_copy_paste2.c\
			line_editor/cut_copy_paste3.c\
			line_editor/history_search.c\
			line_editor/history_search_2.c\
			line_editor/last_command.c\
			line_editor/last_command_2.c\
			line_editor/last_command_3.c\
			exec/exec.c\
			exec/check_binary.c\
			exec/ft_cmdsplit.c\
			exec/routine.c\
			exec/builtin.c\
			exec/extra_exec.c\
			exec/manage_pid.c\
			exec/pid_pipe.c\
			lexer/token.c\
			lexer/lexer.c\
			lexer/sort_token.c\
			lexer/stock_tree.c\
			lexer/node.c\
			lexer/extra_lexer.c\
			lexer/substitution.c\
			redirection/filedescriptor.c\
			redirection/file.c\
			redirection/pipe.c\
			redirection/heredoc.c\
			redirection/aggre.c\
			tools/error.c\
			tools/signals.c\
			tools/tools.c\
			tools/tools_keys.c\
			tools/tools_quote.c\
			tools/tools_extra.c\
			tools/tools_lexer.c\
			tools/tools_redir.c\
			tools/tools_history.c\
			tools/tools_history_2.c\
			tools/tools_routine.c\
			tools/tools_compl.c\
			tools/tools_cd.c\
			built-in/echo.c\
			built-in/env.c\
			built-in/env2.c\
			built-in/cd.c\
			built-in/cd2.c\
			built-in/set_env.c\
			built-in/unsetenv.c\
			built-in/history.c\
			built-in/history_2.c\
			built-in/history_3.c\
			built-in/history_4.c\
			built-in/read/ft_read.c\
			built-in/read/ft_read2.c\
			built-in/read/read_r_opt.c\
			built-in/read/read_without_opt.c\
			built-in/local.c\
			built-in/cmd_loc.c\
			built-in/unset.c\
			built-in/export.c\
			prompt_statement/before_curr_after.c\
			prompt_statement/main_prompt_statement.c\
			prompt_statement/prompt_backslash.c\
			prompt_statement/prompt_date.c\
			prompt_statement/prompt_hostname.c\
			prompt_statement/prompt_octal.c\
			prompt_statement/prompt_path.c\
			prompt_statement/prompt_shellname.c\
			prompt_statement/prompt_time.c\
			prompt_statement/prompt_uid.c\
			prompt_statement/prompt_username.c\
			prompt_statement/prompt_version.c\
			prompt_statement/add_escape.c\
			completion/completion.c\
			completion/list_args.c\
			completion/get_binaries.c\
			completion/display_args.c\
			completion/compl_keys.c\
			completion/compl_arrow.c\
			completion/compl_star.c\
			completion/compl_color.c\
			completion/print_complline.c\
			completion/compl_buff.c\
			completion/compl_free.c

# colors
GRN     =   \033[0;32m
RED     =   \033[0;31m
CYN     =   \033[0;36m
NC      =   \033[0m
SRCS        = $(addprefix $(SRCDIR), $(SRC))
OBJS        = $(addprefix $(OBJDIR), $(SRC:.c=.o))
DEPS		:= $(OBJS:.o=.d)

all: $(OBJDIR) $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -L./$(LIBSRC) -lft -ltermcap -o $(NAME) $(OBJS)
	@echo "\n${CYN}PROCESSING DONE !${NC}"

$(OBJDIR):
	@mkdir -p objs objs/built-in objs/tools objs/exec objs/lexer objs/redirection objs/line_editor objs/completion objs/prompt_statement objs/built-in/read

$(LIB):
	@echo "${CYN}Processing ${NC}./libft/objs ${CYN}[${NC}...${CYN}]${NC}"
	@make -C $(LIBSRC)
	@echo "\n${CYN}Processing ${NC}./objs ${CYN}[${NC}...${CYN}]${NC}"

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER)$(NAME).h
	@echo "${GRN}Compiling${NC} $@"
	@$(CC) $(FLAGS) $(DFLAGS) -c -o $@ $< -I $(HEADER)

clean:
	@echo "${RED}Cleaning ${NC}./objs/ ${RED}[${NC}...${RED}]${NC}"
	@rm -rf $(OBJS)
	@rm -rf $(DEPS)
	@echo "${RED}Cleaning ${NC}./libft/objs/ ${RED}[${NC}...${RED}]${NC}"
	@make -C $(LIBSRC) clean

fclean: clean
	@echo "${RED}Cleaning ${NC}./${RED}$(NAME)${NC}"
	@rm -rf $(NAME)
	@echo "${RED}Cleaning ${NC}./libft/${RED}libft.h${NC}\n"
	@make -C $(LIBSRC) fclean
	@rm -rf objs/
	@echo "${RED}DELETE DONE !${NC}"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
