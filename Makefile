SRC_LAUNCH = ./src/launch/
SRC_MINISHELL = ./src/minishell/
SRC_INPUT = ./src/input/
SRC_VECTOR = ./src/vector/
SRC_PARSER = ./src/parser/

#HEADERS = ./headers/minishell.h ./headers/launch.h
NAME = 21sh
PRINT = lib/printf/libftprintf.a
NAME_MINISHELL = main.c built_ins.c built_ins2.c cpy_func.c launch.c linked_list.c\
				linked_list2.c linked_list3.c sig_handler.c split_line.c utilities.c utilities2.c
NAME_LAUNCH = aux_utilities.c job_process_status.c job_utils.c jobs_builtins.c launch_pro.c parse_helpers.c
NAME_INPUT = assist_func.c cut_copy_paste.c cut_paste.c history_session.c input.c\
			navigation_words.c navigation.c save_buff.c spec_key.c
NAME_VECTOR = vector.c
NAME_PARSER = parser.c replace_env.c write_arg.c replace_dir.c

SRC = 	$(addprefix $(SRC_MINISHELL), $(NAME_MINISHELL))\
		$(addprefix $(SRC_LAUNCH), $(NAME_LAUNCH))\
		$(addprefix $(SRC_INPUT), $(NAME_INPUT))\
		$(addprefix $(SRC_VECTOR), $(NAME_VECTOR))\
		$(addprefix $(SRC_PARSER), $(NAME_PARSER))\

#FLAG = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)
OBJ = *.o

CG = \033[92m
all: start $(NAME)
$(NAME):
	@make -sC ./lib/printf/
	@gcc  -c $(FLAG) $(SRC)
	@gcc  -ltermcap -o $(NAME) $(OBJ) -L. $(PRINT) 
	@rm *.o
	@echo "\r$(CY)--------------------------------------------------- GO --------------------------------------------------------"
start:
	@echo "\r$(CG)compile...																			  "
	@echo "	-------------------------------------------------------------------------------------------------------"
	@echo "	|	                000|             000|               00|       	         	              |	"
	@echo "	|	000000000000|          000000|           000000|    00|  	00000|   00|	    00|       | "
	@echo "	|	000  00  000|	000|   00  00|   000|    000|       000000|	00|      00|	    00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|      0000|    00  00|	00000|   00|        00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|        000|   00  00|	00|  	 00|	    00|       |	"
	@echo "	|	000  00  000|	000|   00  00|   000|    000000|    00  00|	00000|   0000000|   0000000|  |	"
	@echo "	-------------------------------------------------------------------------------------------------------"
clean:
	@make clean -sC lib/printf/
	@rm -rf $(OBJ)
fclean: clean
	@make fclean -sC lib/printf/
	@rm -rf $(NAME)
re: fclean all clean