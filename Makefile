# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 09:07:35 by tbasak            #+#    #+#              #
#    Updated: 2025/05/24 14:21:40 by tbasak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/built_in.c src/cd.c src/create_heredoc.c src/echo.c src/env.c src/exec_utils.c \
	src/exec.c src/exit.c src/expand_variables_utils.c src/expand_variables.c src/export.c \
	src/find_char.c src/free.c src/get_input_data.c src/get_prompt.c src/handlers.c \
	src/init_struct_command.c src/input_checker.c src/main.c src/prompt.c src/pwd.c \
	src/redirection_utils.c src/redirection.c src/remove_all_quotes.c \
	src/sort_and_print_tab.c src/split_limited.c src/split_space_limited.c \
	src/tab.c src/unset.c src/utils.c src/shlvl.c src/env_utils.c src/prompt_expanded.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./Libft

#				Réinitialisation
RESET=			"\033[0m"
#				Styles
BOLD=			"\033[1m"
DIM=			"\033[2m"
ITALIC=			"\033[3m"
UNDERLINE=		"\033[4m"
BLINK=			"\033[5m"
REVERSE=		"\033[7m"
HIDDEN=			"\033[8m"
#				Couleurs texte
BLACK=			"\033[0;30m"
RED=			"\033[0;31m"
GREEN=			"\033[0;32m"
YELLOW=			"\033[0;33m"
BLUE=			"\033[0;34m"
MAGENTA=		"\033[0;35m"
CYAN=			"\033[0;36m"
WHITE=			"\033[0;37m"
#				Couleurs texte en gras
BBLACK=			"\033[1;30m"
BRED=			"\033[1;31m"
BGREEN=			"\033[1;32m"
BYELLOW=		"\033[1;33m"
BBLUE=			"\033[1;34m"
BMAGENTA=		"\033[1;35m"
BG_CYAN=		"\033[46m"
BG_WHITE=		"\033[47m"
#				Couleurs de fond vives
BG_BBLACK=		"\033[100m"
BG_BRED=		"\033[101m"
BG_BGREEN=		"\033[102m"
BG_BYELLOW=		"\033[103m"
BG_BBLUE=		"\033[104m"
BG_BMAGENTA=	"\033[105m"
BG_BCYAN=		"\033[106m"
BG_BWHITE=		"\033[107m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C Libft || (echo ${BRED}"[ERROR] COMPILATION FAILED !"${RESET} && exit 1)
	@echo ${BYELLOW}"[INFO] COMPILING MINISHELL..."${RESET}
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./Libft -lft -lreadline || (echo ${BRED}"[ERROR] COMPILATION FAILED !"${RESET} && exit 1)
	@echo ${BGREEN}"[SUCCESS] MINISHELL COMPILED."${RESET}

all: $(NAME)

clean:
	@echo ${BYELLOW}"[INFO] CLEANING OBJECTS..."${RESET}
	@rm -f $(OBJ) || (echo ${BRED}"[ERROR] OBJECTS CLEANING FAILED !"${RESET} && exit 1)
	@echo ${BGREEN}"[SUCCESS] OBJECTS CLEANED."${RESET}

fclean: clean
	@make -C Libft fclean
	@echo ${BYELLOW}"[INFO] CLEANING EXECUTABLE..."${RESET}
	@rm -f $(NAME) .minishell_history || (echo ${BRED}"[ERROR] EXECUTABLE CLEANING FAILED !"${RESET} && exit 1)
	@echo ${BGREEN}"[SUCCESS] EXECUTABLE CLEANED."${RESET}

re: fclean all
	@echo ${BGREEN}"[SUCCESS] MINISHELL RECOMPILED."${RESET}

shell:
	@echo ${BYELLOW}"[INFO] RUNNING MINISHELL..."${RESET}
	@./$(NAME) || (echo ${BRED}"[ERROR] MINISHELL FAILED TO START !"${RESET} && exit 1)
	@echo ${BYELLOW}"[INFO] MINISHELL TERMINATED."${RESET}

valgrind:
	@echo ${BYELLOW}"[INFO] RUNNING VALGRIND..."${RESET}
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes -s ./$(NAME) || (echo ${BRED}"[ERROR] VALGRIND FAILED !"${RESET} && exit 1)
	@echo ${BYELLOW}"[INFO] VALGRIND TERMINATED."${RESET}

.PHONY: all clean fclean re shell valgrind
