SRC_21SH = ./src/21sh/
SRC_LAUNCH = ./src/launch/
SRC_MINISHELL = ./src/minishell/
SRC_INPUT = ./src/input/
SRC_VECTOR = ./src/vector/
SRC_PARSER = ./src/parser/
SRC_LEXER = ./src/lexer/
SRC_VECTOR_LIB = ./lib/vector/
SRC_ALIAS = ./src/alias/
SRC_HASH = ./src/hashtable/
SRC_SET = ./src/set/
SRC_ENV = ./src/env/
SRC_PAR_EXP = ./src/parser/param_exp_func/
SRC_FLAGS = ./src/flags/

SRC_DLIST = ./src/vi_mode/dlist/
SRC_FT_STRING = ./src/vi_mode/ft_string/
SRC_VI_INPUT = ./src/vi_mode/src/input/
SRC_COPY_MODE = ./src/vi_mode/src/copy_mode/
SRC_EDIT_STRING_HISTORY = ./src/vi_mode/src/edit_string_history/
SRC_VI_HS = ./src/vi_mode/src/history_search/
SRC_RL = ./src/vi_mode/src/input/rl_mode/
SRC_VI = ./src/vi_mode/src/input/vi_mode/
SRC_HS = ./src/history_search/src/

INCLUDES  = -I./headers/
INCLUDES += -I./lib/printf/
INCLUDES += -I./lib/printf/libft/
INCLUDES += -I./src/vi_mode/dlist/
INCLUDES += -I./src/vi_mode/ft_string/
INCLUDES += -I./src/vi_mode/headers/
INCLUDES += -I./src/history_search/headers/


NAME = 42sh
PRINT = lib/printf/libftprintf.a
NAME_21SH = main.c kazekage.c assist_21sh.c built_in_type.c
NAME_MINISHELL = built_ins.c cpy_func.c launch.c linked_list.c\
				linked_list2.c linked_list3.c sig_handler.c utilities.c utilities2.c environments.c \
				cd.c cd_flags.c cd_path.c
				
NAME_LAUNCH = aux_utilities.c job_process_status.c job_utils.c jobs_builtins.c launch_pro.c job_utils_print.c\
				heredoc_input.c child_launch_proc.c holder_launch_struct.c jobs_fg_bg_builtin.c jobs_kill_builtin.c\
				out_redir_launch.c pipe_and_preconfig.c fork_after_check_exist.c check_access.c
NAME_INPUT = assist_func.c key_backspace.c key_copy.c key_cut.c key_paste.c key_endhome.c history_session.c input.c\
			navigation_words.c navigation_line.c save_buff.c spec_key.c set_termcap.c multiple_promt.c key_control.c\
			fill_hsees_search.c
NAME_VECTOR = vector.c
NAME_PARSER = parser.c replace_env.c write_arg.c replace_dir.c get_token.c assist_parser.c parse_error.c multiple_line.c \
                replace_alias.c replace_param.c parser_error.c match.c ft_strrev.c replace_param_action.c
NAME_LEXER = lexer.c new_segment.c input_path.c output_path.c  free_job.c new_query.c new_agregation.c
NAME_VECTOR_LIB = vector_add.c vector_deinit.c vector_del_value.c vector_del.c vector_get.c vector_init.c vector_resize.c \
				vector_search.c vector_set.c
NAME_ALIAS = alias_deinit.c alias_get.c alias_init.c alias_print.c alias_set.c alias_unset.c alias_update.c ms_alias.c \
				ms_unalias.c
NAME_HASH = ft_path.c hash_free.c hash_functions.c hash_main.c phash_init_builtins.c phash_init.c phash_search.c \
			phash_update.c phash_init_param_exp.c
NAME_SET = ms_export.c ms_set.c ms_unset.c set.c set_deinit.c set_get.c set_init.c set_print.c set_update.c unset.c \
            set_handler.c
NAME_ENV = env.c
NAME_PAR_EXP = colon.c equal.c hash_d.c hash.c minus.c percent_d.c percent.c plus.c question.c get_status.c
NAME_FLAGS = flags_parse.c

## vi_mode
NAME_DLIST = ft_dlist_new.c ft_dlist_add.c ft_dlist_delone.c ft_dlist_rewind.c ft_dlist_del.c ft_dlist_addbegin.c \
			ft_dlist_addback.c ft_dlist_size.c

NAME_FT_STRING = str_addback.c str_new.c str_substr.c str_union.c

NAME_VI_INPUT = in_arrow.c in_command_line.c in_ft_keys.c in_ft_put.c \
				in_ft_quotes.c in_bracket.c in_wait_input.c \
				in_wait_input_default.c in_wait_input_vi.c in_wait_input_rl.c

NAME_COPY_MODE = cm_copy_mode.c cm_func.c

NAME_EDIT_STRING_HISTORY = eh_ft_undo.c eh_ft_list_del.c

NAME_VI_HS = hi_search_history.c

NAME_RL = ft_swap_chars.c ft_swap_words.c

NAME_VI = vi_a.c vi_ab.c vi_arr_up.c vi_b.c vi_c.c \
		vi_comma.c vi_d.c vi_dollar.c vi_e.c vi_f.c \
		vi_fb.c vi_grill.c vi_h.c vi_i.c vi_ib.c \
		vi_j.c vi_k.c vi_l.c vi_p.c vi_pipe.c vi_r.c \
		vi_rb.c vi_sb.c vi_semicolon.c vi_u.c vi_v.c \
		vi_w.c vi_x.c vi_xb.c vi_y.c vi_zero.c

NAME_HS = history_search.c search_utils.c shell_fc.c \
		  print_history.c key_search.c save_history.c


SRC = 	$(addprefix $(SRC_21SH), $(NAME_21SH))\
		$(addprefix $(SRC_MINISHELL), $(NAME_MINISHELL))\
		$(addprefix $(SRC_LAUNCH), $(NAME_LAUNCH))\
		$(addprefix $(SRC_INPUT), $(NAME_INPUT))\
		$(addprefix $(SRC_VECTOR), $(NAME_VECTOR))\
		$(addprefix $(SRC_PARSER), $(NAME_PARSER))\
		$(addprefix $(SRC_LEXER), $(NAME_LEXER))\
		$(addprefix $(SRC_DLIST), $(NAME_DLIST))\
		$(addprefix $(SRC_FT_STRING), $(NAME_FT_STRING))\
		$(addprefix $(SRC_VI_INPUT), $(NAME_VI_INPUT))\
		$(addprefix $(SRC_COPY_MODE), $(NAME_COPY_MODE))\
		$(addprefix $(SRC_EDIT_STRING_HISTORY), $(NAME_EDIT_STRING_HISTORY))\
		$(addprefix $(SRC_VI_HS), $(NAME_VI_HS))\
		$(addprefix $(SRC_RL), $(NAME_RL))\
		$(addprefix $(SRC_VI), $(NAME_VI))\
		$(addprefix $(SRC_VECTOR_LIB), $(NAME_VECTOR_LIB))\
		$(addprefix $(SRC_ALIAS), $(NAME_ALIAS))\
		$(addprefix $(SRC_HASH), $(NAME_HASH))\
		$(addprefix $(SRC_SET), $(NAME_SET))\
		$(addprefix $(SRC_ENV), $(NAME_ENV))\
		$(addprefix $(SRC_HS), $(NAME_HS))\
		$(addprefix $(SRC_PAR_EXP), $(NAME_PAR_EXP))\
		$(addprefix $(SRC_FLAGS), $(NAME_FLAGS))\


FLAG = -Wall -Werror -Wextra -g
OBJ = $(SRC:.c=.o)
OBJ = *.o

CG = \033[92m
all: start $(NAME)
$(NAME):
	@make -sC ./lib/printf/
	@gcc  -c $(FLAG) $(SRC) $(INCLUDES)
	@gcc  -ltermcap -o $(NAME) $(OBJ) -L. $(PRINT) $(INCLUDES)

	@echo "\r$(CY)------------ GO -----------------"
start:
	@echo "\r$(CG)compile..."
	@echo "	------------------------------"
	@echo "	|	000   000|     0000|   |"
	@echo "	|	000   000|   0000000|  |"
	@echo "	|	000   000|       000|  |"
	@echo "	|	000000000|     000|    |"
	@echo "	|	      000|   000|      |"
	@echo "	|	      000|  00000000|  |"
	@echo "	------------------------------"
clean:
	@make clean -sC lib/printf/
	@rm -rf $(OBJ)
fclean: clean
	@make fclean -sC lib/printf/
	@rm -rf $(NAME)
re: fclean all clean
