# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-hass <rel-hass@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 09:07:35 by tbasak            #+#    #+#              #
#    Updated: 2025/04/02 07:32:51 by rel-hass         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(shell find src -name "*.c")

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./util/include

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
	@make -C util || (echo ${BRED}"[ERROR] COMPILATION FAILED !"${RESET} && exit 1)
	@echo ${BYELLOW}"[INFO] COMPILING MINISHELL..."${RESET}
	@$(CC) $(CFLAGS) $(OBJ) -L./util -lutil -o $(NAME) -lreadline || (echo ${BRED}"[ERROR] COMPILATION FAILED !"${RESET} && exit 1)
	@echo ${BGREEN}"[SUCCESS] MINISHELL COMPILED."${RESET}

all: $(NAME)

clean:
	@echo ${BYELLOW}"[INFO] CLEANING OBJECTS..."${RESET}
	@rm -f $(OBJ) || (echo ${BRED}"[ERROR] OBJECTS CLEANING FAILED !"${RESET} && exit 1)
	@echo ${BGREEN}"[SUCCESS] OBJECTS CLEANED."${RESET}

fclean: clean
	@make -C util fclean
	@echo ${BYELLOW}"[INFO] CLEANING EXECUTABLE..."${RESET}
	@rm -f $(NAME) || (echo ${BRED}"[ERROR] EXECUTABLE CLEANING FAILED !"${RESET} && exit 1)
	@echo ${BGREEN}"[SUCCESS] EXECUTABLE CLEANED."${RESET}

re: fclean all
	@echo ${BGREEN}"[SUCCESS] MINISHELL RECOMPILED."${RESET}

shell:
	@echo ${BYELLOW}"[INFO] RUNNING MINISHELL..."${RESET}
	@./$(NAME) || (echo ${BRED}"[ERROR] MINISHELL FAILED TO START !"${RESET} && exit 1)
	@echo ${BYELLOW}"[INFO] MINISHELL TERMINATED."${RESET}

.PHONY: all clean fclean re shell
