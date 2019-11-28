/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:47:14 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/28 20:05:47 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include "launch.h"
# include "input.h"
# include "parser.h"
# include "term.h"
# include "lexer.h"
# include "vi_input.h"
# include "history_search.h"

# include "hashtable.h"
# include "alias.h"
# include "../lib/printf/ft_printf.h"
# include "../lib/printf/libft/get_next_line.h"
# include "set.h"
# define BUFF_LN 5
# define CHANGE_ENV { free(g_sh->env[i]); g_sh->env[i] = tm;return (1);}
# define FU_TERMCAPS 0

# define S_SUBSTITUTE 0
# define S_ASSIGN 1
# define S_ERROR 2

# define S_PARAMETER 0
# define S_WORD 1
# define S_NULL 2

# define S_MINUS 0
# define S_EQUAL 1
# define S_QUEST 2
# define S_PLUS 3
# define S_PERCENT 4
# define S_PERCENT_D 5
# define S_HASH 6
# define S_HASH_D 7

# define S_SET 0
# define S_SET_NULL 1
# define S_UNSET 2

# define CD_L_FLAG 1
# define CD_P_FLAG 2

# define SIG_PROC signal(SIGTTOU, SIG_IGN); tcsetpgrp(0, getpid())

# define HISTORY_FILE ".42sh_history"

/*
** 		t_env linked list structure
*/

typedef struct			s_vault
{
	int					index;
	char				key[50];
	char				path[200];
	struct s_vault		*next;
}						t_vault;

typedef struct			s_env
{
	int					index;
	char				**c_env;
	char				builtin_str[7][20];
	int					(*builtin_func[7]) ();
	int					i;
	struct s_vault		*vault;
	void				(*update_envv)();
	void				(*print_envv)();
	void				(*get_dir)();
}						t_env;

typedef struct			s_expansion
{
	char				*param;
	char				*word;
	char				*env;
	int					flag_hash;
	int					flag_exp;
	char				*action;
	char				(*f)(struct s_expansion *exp);
}						t_exp;

typedef void			(*t_callback)(t_vault *data);

t_vault					*create_env(int index, char *env, t_vault *next);
t_vault					*prepend_env(t_vault *head, char *line);
t_vault					*append_env(t_vault *head, char *env);
t_vault					*remove_front_env(t_vault *head);
t_vault					*remove_back_env(t_vault *head);
t_vault					*remove_any_env(t_vault *head, t_vault *nd);
t_vault					*search_key(t_vault *head, char *key);
void					dispose_env(t_vault *head);
int						count_env(t_vault *head);
void					display_env(t_vault *n);
void					traverse(t_vault *head, t_callback f);
void					grab_vault(t_vault *n);
void					update_env(void);
void					clean_up(void);

/*
** 		minishell core-functions
*/

t_env					*g_env;
char					*read_ln(void);
char					**line_split(char const *s, char *delim);
int						launch_dispatcher(char **args);
int						launch_proc(char **args, char **path, char *str, int i);
t_vault					*environ_grab(t_vault *root);
char					*env_path(char *key);
char					*ft_strjoiner(char const *s1, char const *s2);

void					proc_signal_handler(int signo);
void					signal_handler(int signo);
void					get_cwd(char *str);
void					string_var_parser(char **line);
char					*strcpy_till_n(char *dst, const char *src, char c);
void					sh_print_promt(void);
void					key_search(t_history_session *h_session);

void					parser_error_set(char *msg);
int						parser_error_print(char **arg);

/*
** 				ENV
*/

char					**init_environ(char **env);
int						print_env(t_process *proc);
int						setenv_(t_process *proc);
char					*get_env(char *varible);
int						remove_env(t_process *proc);
int						unset_(t_process *proc);

char					*new_env_join(char *name, char *value);
int						set_env(char *name, char *value);

/*
** 		built-ins funcs
*/

int						cd_(t_process *proc);
int						cd_check_flags(char *flags);
int						cd_ext(char *path);
void					set_pwd(char *path);
int						help_shell(t_process *proc);
int						exit_shell(t_process *proc);
int						echo(t_process *proc);
int						num_shell_functions(t_process *proc);
int						type_shell(t_process *proc);
int						shell_fc(t_process *proc);

/*
** 		assist_21sh
*/
void					sigint_handler(int signal);
char					*flags_parse(char **argv, int *i);

/*
** 		param expansion
*/
void					free_exp(t_exp *exp);

char					*param_exp_minus(t_exp *exp);
char					*param_exp_plus(t_exp *exp);
char					*param_exp_equal(t_exp *exp);
char					*param_exp_question(t_exp *exp);
char					*param_exp_colon(t_exp *exp);
char					*param_exp_percent(t_exp *exp);
char					*param_exp_percent_d(t_exp *exp);
char					*param_exp_hash(t_exp *exp);
char					*param_exp_hash_d(t_exp *exp);
char					*get_status(t_exp *exp);

#endif
