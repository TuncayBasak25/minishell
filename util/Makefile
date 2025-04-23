NAME = libutil.a
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include

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
BCYAN=			"\033[1;36m"
BWHITE=			"\033[1;37m"
#				Couleurs de fond
BG_BLACK=		"\033[40m"
BG_RED=			"\033[41m"
BG_GREEN=		"\033[42m"
BG_YELLOW=		"\033[43m"
BG_BLUE=		"\033[44m"
BG_MAGENTA=		"\033[45m"
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

all: $(OBJ)
	@echo $(BYELLOW)"[INFO] CREATING LIBRARY..."$(RESET)
	@ar rcs $(NAME) $(OBJ) || (echo $(BRED)"[ERROR] LIBRARY CREATION FAILED !"$(RESET) && exit 1)
	@echo $(BGREEN)"[SUCCESS] LIBRARY CREATED: $(NAME)"$(RESET)


clean:
	@echo $(BYELLOW)"[INFO] REMOVING OBJECT FILES..."$(RESET)
	@rm -f $(OBJ) || (echo $(BRED)"[ERROR] OBJECT FILES REMOVAL FAILED !"$(RESET) && exit 1)
	@echo $(BGREEN)"[SUCCESS] OBJECT FILES REMOVED."$(RESET)

fclean: clean
	@echo $(BYELLOW)"[INFO] REMOVING LIBRARY..."$(RESET)
	@rm -f $(NAME)	|| (echo $(BRED)"[ERROR] LIBRARY REMOVAL FAILED !"$(RESET) && exit 1)
	@echo $(BGREEN)"[SUCCESS] LIBRARY REMOVED."$(RESET)

re: fclean all
	@echo $(BGREEN)"[SUCCESS] LIBRARY REBUILT: $(NAME)"$(RESET)

.PHONY: all clean fclean re