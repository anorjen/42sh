# COLORS

CYAN = \033[1;96m
YEL = \033[0;33m
GRN = \033[0;32m
RESET = \033[0m

# MAIN CONFIG

21_SHELL = 21sh

# GCC COMPILATOR PART CONF

CC = gcc
# FLAGS = -Wall -Wextra -Werror
LIBRARIES = -lft -L$(PRINTF_DIR)
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(PRINTF_HEADERS)ft_printf.h

# LIB SRC AND DST PART CONF

PRINTF = $(PRINTF_DIR)libftprintf.a
PRINTF_DIR = ./lib/printf/
PRINTF_HEADERS = $(PRINTF_DIR)

HEADERS_LIST = minishell.h
HEADERS_DIRECTORY = ./src/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

#	Функция addprefix добавляет свой первый аргумент ко всем целям, 
#	которые задает второй аргумент.

SRC_DIR = ./src/
# SRC_DIR2 = ./src/launch/

SRC_LST = built_ins.c built_ins2.c cpy_func.c launch.c linked_list.c\
 linked_list2.c linked_list3.c sig_handler.c split_line.c utilities.c utilities2.c\
 aux_utilities.c job_process_status.c job_utils.c jobs_builtins.c launch_pro.c parse_helpers.c job_utils_print.c

# SRC_LST2 = aux_utilities.c job_process_status.c job_utils.c jobs_builtins.c\
launch_pro.c parse_helpers.c job_utils_print.c

SRC_FT_MINISHELL = main.c

SOURCES = $(addprefix $(SRC_DIR), $(SRC_LST)) $(addprefix $(SRC_DIR), $(SRC_LST))
SOURCES_FT_MINISHELL = $(addprefix $(SRC_DIR), $(SRC_FT_MINISHELL))


# 	Функция patsubsb уберет префикс ../../ у имен файлов (она заменяет шаблон, 
#	заданный первым аргументом на шаблон во втором аргументе, а % обозначает любое количество символов)

OBJ_DIR = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SRC_LST))
OBJECTS_LIST_LS = $(patsubst %.c, %.o, $(SRC_FT_MINISHELL))
OBJECTS	= $(addprefix $(OBJ_DIR), $(OBJECTS_LIST))
OBJECTS_LS = $(addprefix $(OBJ_DIR), $(OBJECTS_LIST_LS))

.PHONY: all clean fclean re

#	RULES and stuff

all: $(21_SHELL)

$(21_SHELL): $(PRINTF) $(OBJ_DIR) $(OBJECTS) $(OBJECTS_LS)
	@$(CC) $(FLAGS) $(PRINTF) $(INCLUDES) $(OBJECTS) $(OBJECTS_LS) -o $(21_SHELL)
	@echo "\n$(21_SHELL): $(CYAN)$(21_SHELL) object files were created$(RESET)"
	@echo "$(21_SHELL): $(GRN)$(21_SHELL) was created$(RESET)"



$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(21_SHELL): $(CYAN)$(OBJ_DIR) was created$(RESET)"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(CYAN).$(RESET)\c"

$(PRINTF):
	@echo "$(21_SHELL): $(CYAN)creating $(PRINTF)...$(RESET)"
	@$(MAKE) -sC $(PRINTF_DIR)

clean:
	@$(MAKE) -sC $(PRINTF_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(21_SHELL): $(YEL)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(21_SHELL): $(YEL)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(PRINTF)
	@echo "$(21_SHELL): $(YEL)$(PRINTF) was deleted$(RESET)"
	@rm -f $(21_SHELL)
	@echo "$(21_SHELL): $(YEL)$(21_SHELL) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all