/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:41:22 by yharwyn-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/10/19 15:48:27 by sbearded         ###   ########.fr       */
=======
/*   Updated: 2019/10/19 19:26:29 by anorjen          ###   ########.fr       */
>>>>>>> anorjen
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
# define BUFF_LN 5
# define CHANGE_ENV { free(g_sh->env[i]); g_sh->env[i] = tm;return (1);}
# define FU_TERMCAPS 0

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
int						help_shell(t_process *proc);
int						exit_shell(t_process *proc);
int						echo(t_process *proc);
int						num_shell_functions(t_process *proc);
int						type_shell(t_process *proc);
int     				shell_fc(t_process *proc);

/*
** 		assist_21sh
*/
void					sigint_handler(int signal);

#endif
